# 24/08/2019: Manual repository fix needed

The repository split has caused existing repository `git pull` commands
to fail. Run the following commands to fix it. Apologies.

    cd /var/db/kiss
    rm -rf repo
    git clone https://github.com/kisslinux/repo
