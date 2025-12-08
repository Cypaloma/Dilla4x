#!/bin/bash
set -e

# Configuration
LOCAL_WIKI_DIR="wiki"
WIKI_REPO_URL="git@github.com:Cypaloma/Dilla4x.wiki.git"
TEMP_DIR="/tmp/dilla4x_wiki_deploy"

echo "📘 Dilla4x Wiki Deployer"
echo "========================"

# Check if git is installed
if ! command -v git &> /dev/null; then
    echo "❌ git is not installed."
    exit 1
fi

# Ensure we are in the project root
if [ ! -d "$LOCAL_WIKI_DIR" ]; then
    echo "❌ Could not find '$LOCAL_WIKI_DIR' directory. Run this from the project root."
    exit 1
fi

# Get Wiki URL
if [ -z "$WIKI_REPO_URL" ]; then
    echo "ℹ️  Enter your GitHub Wiki Git URL."
    echo "   (Found in the 'Clone this wiki locally' box on the GitHub Wiki page)"
    read -p "   URL: " WIKI_REPO_URL
fi

if [ -z "$WIKI_REPO_URL" ]; then
    echo "❌ URL is required."
    exit 1
fi

echo "🔄 Cloning wiki repo to temporary directory..."
rm -rf "$TEMP_DIR"
git clone "$WIKI_REPO_URL" "$TEMP_DIR"

# Copy everything from local wiki to temp wiki
# First, clean the temp dir safely (remove everything except .git)
cd "$TEMP_DIR"
find . -maxdepth 1 -not -name '.git' -not -name '.' -exec rm -rf {} +
cd - > /dev/null

cp -r "$LOCAL_WIKI_DIR"/* "$TEMP_DIR/"

echo "🚀 Deploying updates..."
cd "$TEMP_DIR"

if [ -z "$(git status --porcelain)" ]; then 
    echo "✅ Wiki is already up to date!"
else 
    git add .
    git commit -m "Wiki Update: $(date)"
    git push origin master
    echo "✅ Wiki deployed successfully!"
fi

# Cleanup
rm -rf "$TEMP_DIR"
echo "✨ Done."
