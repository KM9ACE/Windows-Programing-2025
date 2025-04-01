Owner@DESKTOP-82KFQLK MINGW64 ~
$ cd d:

Owner@DESKTOP-82KFQLK MINGW64 /d
$ cd KM9ACE

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE
$ ls
Windows-Programing-2025/

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE
$ cd Windows-Programing-2025/

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        Project1.sln
        Project1/

nothing added to commit but untracked files present (use "git add" to track)

config 이메일 아이디 등등

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git add .

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   Project1.sln
        new file:   Project1/Project1.vcxproj
        new file:   Project1/Project1.vcxproj.filters


Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git conmit
git: 'conmit' is not a git command. See 'git --help'.

The most similar command is
        commit

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git commit

기억이 날 지는 모르겠는데 아무튼 보냄

[main 2c7f0c2] 정해영
 3 files changed, 186 insertions(+)
 create mode 100644 Project1.sln
 create mode 100644 Project1/Project1.vcxproj
 create mode 100644 Project1/Project1.vcxproj.filters

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git status
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git push
info: please complete authentication in your browser...
Enumerating objects: 7, done.
Counting objects: 100% (7/7), done.
Delta compression using up to 12 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 2.37 KiB | 2.37 MiB/s, done.
Total 6 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/KM9ACE/Windows-Programing-2025.git
   6cdc8d4..2c7f0c2  main -> main

Owner@DESKTOP-82KFQLK MINGW64 /d/KM9ACE/Windows-Programing-2025 (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean