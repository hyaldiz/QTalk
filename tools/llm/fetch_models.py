#!/usr/bin/env python3
"""
fetch_models.py

Updated: If --list is not provided, the default model
TheBloke/deepseek-coder-1.3b-instruct-GGUF|deepseek-coder-1.3b-instruct.Q2_K.gguf
will be downloaded.
"""
import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

def which(cmd):
    return shutil.which(cmd) is not None

def run(cmd, check=True, env=None):
    print("RUN:", " ".join(cmd))
    return subprocess.run(cmd, check=check, env=env)

def try_install_git_lfs():
    if which("git-lfs"):
        print("git-lfs is already installed.")
        return True

    print("git-lfs not found — attempting to install...")
    platform = sys.platform
    try_cmds = []

    if platform.startswith("linux"):
        distro = "unknown"
        try:
            with open("/etc/os-release", "r") as f:
                data = f.read().lower()
                if "ubuntu" in data or "debian" in data:
                    distro = "debian"
                elif "fedora" in data or "centos" in data:
                    distro = "fedora"
                elif "arch" in data:
                    distro = "arch"
        except Exception:
            pass

        if distro == "debian":
            try_cmds = [
                ["sudo", "apt", "update"],
                ["sudo", "apt", "install", "-y", "git-lfs"]
            ]
        elif distro == "fedora":
            try_cmds = [
                ["sudo", "dnf", "install", "-y", "git-lfs"]
            ]
        elif distro == "arch":
            try_cmds = [
                ["sudo", "pacman", "-Syu", "--noconfirm", "git-lfs"]
            ]
        else:
            try_cmds = [
                ["bash", "-lc", "curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash"],
                ["sudo", "apt-get", "install", "-y", "git-lfs"]
            ]

    elif platform == "darwin":
        try_cmds = [
            ["brew", "install", "git-lfs"]
        ]
    elif platform.startswith("win"):
        print("Windows: please install Git LFS using chocolatey or the official installer (e.g., choco install git-lfs).")
        return False
    else:
        print("Unknown platform:", platform)
        return False

    for c in try_cmds:
        try:
            run(c)
        except subprocess.CalledProcessError as e:
            print("Command failed:", c, "— trying next option.")
            continue

    try:
        run(["git", "lfs", "install"])
    except Exception as e:
        print("Error during 'git lfs install':", e)
        return which("git-lfs")

    return which("git-lfs")

def clone_and_pull_lfs(repo_id, dest_root: Path):
    target_dir = dest_root / repo_id.replace("/", "_")
    if target_dir.exists():
        print(f"Already cloned: {target_dir}. Running 'git pull' to update.")
        try:
            run(["git", "-C", str(target_dir), "pull"])
        except subprocess.CalledProcessError:
            print("Pull failed, continuing anyway.")
    else:
        try:
            run(["git", "clone", f"https://huggingface.co/{repo_id}", str(target_dir)])
        except subprocess.CalledProcessError as e:
            print("git clone failed:", e)
            return False

    try:
        run(["git", "-C", str(target_dir), "lfs", "pull"])
        run(["git", "-C", str(target_dir), "lfs", "fetch", "--all"])
        run(["git", "-C", str(target_dir), "lfs", "checkout"])
    except subprocess.CalledProcessError as e:
        print("Error during git lfs pull/fetch/checkout:", e)
        return False

    return True

def hf_download_file(repo_id, filename, outdir: Path, token=None):
    try:
        from huggingface_hub import hf_hub_download
    except Exception:
        print("huggingface_hub not installed — installing...")
        run([sys.executable, "-m", "pip", "install", "huggingface_hub"])
        from huggingface_hub import hf_hub_download

    kwargs = {"repo_id": repo_id, "filename": filename}
    if token:
        os.environ["HF_TOKEN"] = token

    print(f"Downloading via HuggingFace API: {repo_id} / {filename}")
    try:
        path = hf_hub_download(**kwargs)
        dest = outdir / Path(filename).name
        if Path(path) != dest:
            shutil.copy(path, dest)
        print("Downloaded:", dest)
        return True
    except Exception as e:
        print("hf_hub_download error:", e)
        return False

def parse_list_file(list_path: Path):
    items = []
    with open(list_path, "r", encoding="utf-8") as f:
        for raw in f:
            s = raw.strip()
            if not s or s.startswith("#"):
                continue
            parts = s.split("|")
            if len(parts) == 1:
                items.append((parts[0].strip(), None))
            else:
                items.append((parts[0].strip(), parts[1].strip()))
    return items

def main():
    p = argparse.ArgumentParser(description="Install git-lfs (if needed) and fetch models from HuggingFace. Default model used if --list not provided.")
    p.add_argument("--list", "-l", required=False, help="Model list file. Each line: repo_id|filename  (filename optional)")
    p.add_argument("--outdir", "-o", default="models", help="Output directory")
    p.add_argument("--use-hf", action="store_true", help="Use huggingface_hub download instead of git clone + git lfs pull")
    p.add_argument("--hf-token", default=None, help="HuggingFace token (optional). Or set HF_TOKEN env var.")
    p.add_argument("--no-install-git-lfs", action="store_true", help="Skip attempting to install git-lfs (if not present).")
    args = p.parse_args()

    outdir = Path(args.outdir).expanduser()
    outdir.mkdir(parents=True, exist_ok=True)

    # Default single model if --list not provided
    default_items = [("TheBloke/deepseek-coder-1.3b-instruct-GGUF", "deepseek-coder-1.3b-instruct.Q2_K.gguf")]

    if args.list:
        list_path = Path(args.list).expanduser()
        if not list_path.exists():
            print("List file not found:", list_path)
            sys.exit(2)
        items = parse_list_file(list_path)
        if not items:
            print("No models in list.")
            sys.exit(0)
    else:
        print("--list not provided. Using default model:", default_items[0])
        items = default_items

    hf_token = args.hf_token or os.environ.get("HF_TOKEN")

    if args.use_hf:
        print("Direct download via huggingface_hub selected.")
        for repo, filename in items:
            if filename:
                ok = hf_download_file(repo, filename, outdir, token=hf_token)
                if not ok:
                    print("Download failed:", repo, filename)
            else:
                print("WARNING: filename not specified. 'repo_id|filename' format is recommended when using huggingface_hub.")
        return

    if not which("git"):
        print("git not found. Please install git on your system.")
        sys.exit(1)

    if not which("git-lfs"):
        if args.no_install_git-lfs:
            print("git-lfs missing and --no-install-git-lfs given. Exiting.")
            sys.exit(1)
        ok = try_install_git_lfs()
        if not ok:
            print("git-lfs installation failed. Try using --use-hf for alternative download method.")
            sys.exit(1)

    for repo, filename in items:
        print("Processing:", repo, filename)
        ok = clone_and_pull_lfs(repo, outdir)
        if not ok:
            print("clone/pull failed, attempting fallback via huggingface_hub (if filename is provided).")
            if filename:
                hf_ok = hf_download_file(repo, filename, outdir, token=hf_token)
                if not hf_ok:
                    print("Fallback download also failed:", repo, filename)
            else:
                print("No filename provided, skipping fallback.")
        else:
            print("Repository cloned and LFS objects successfully downloaded.")

    print("Done. Models are in:", outdir)
    print("Note: If files appear as text pointers, try running 'git lfs pull' or use huggingface_hub.")

if __name__ == "__main__":
    main()

