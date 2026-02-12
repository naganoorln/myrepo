First Time Git Commit (Step-by-Step)
This guide explains how to create a Git repository, connect it to GitHub, and make your first commit.

1. Install Git

Check if Git is installed:

git --version


If not installed:

Windows / macOS / Linux: https://git-scm.com/downloads

2. Configure Git (One Time Only)

Set your name and email (used in commits):

git config --global user.name "Your Name"
git config --global user.email "your-email@example.com"


Verify:

git config --list

3. Create a Project Folder
mkdir my-project
cd my-project

4. Initialize Git Repository
git init


This creates a hidden .git folder (your local repository).

5. Create Files

Example:

touch README.md


Edit README.md and add content.

6. Check Git Status
git status


Shows untracked or modified files.

7. Add Files to Staging Area

Add all files:

git add .


Or add a specific file:

git add README.md

8. Commit Changes
git commit -m "Initial commit"


This saves a snapshot of your project.

9. Create a GitHub Repository

Go to https://github.com

Click New Repository

Enter repository name

Do NOT initialize with README

Click Create repository

10. Connect Local Repo to GitHub

Copy the repo URL, then run:

git remote add origin https://github.com/USERNAME/REPOSITORY.git


Verify:

git remote -v

11. Set Main Branch (If Needed)
git branch -M main

12. Push to GitHub
git push -u origin main


Now your code is live on GitHub 🎉

Common Commands Summary
git status        # Check file status
git add .         # Stage all files
git commit -m ""  # Commit changes
git push          # Upload to GitHub
git pull          # Download updates

What is origin/main?

origin → remote GitHub repository

main → default branch

origin/main → main branch on GitHub (remote)

Done 

You’ve successfully created a repository and made your first Git commit!



Generate GitHub Personal Access Token (classic)
https://github.com/settings/tokens

Once you open that, choose “Tokens (classic)” and then “Generate new token”.

Step-by-step within the link

Open the link above in your browser

If prompted, log into your GitHub account

In Personal access tokens → Tokens (classic) click:
Generate new token (classic)

Enter a Note/Name (e.g., VM Git token)

Choose expiration (e.g., 90 days or longer)

Under Scopes, check:

repo (for access to repositories)

Scroll down and click Generate token

Copy the token (ghp_...) immediately — you won’t see it again
