# CS362-F2019

OSU CS362 Software Engineering II Fall 2019

## Git Documentation for Teammates

To start, clone the repository to a directory on your computer:

`git clone https://github.com/cmatian/CS362-F2019.git`

Enter the directory in the terminal and check the existing branches: `git branch -a`

The repo should have the `matianc-finalproject-bugs` branch locally. Otherwise, it will exist on the remote server. In any case, you can simply checkout the directory by doing:

`git checkout matianc-finalproject-bugs`

This is the branch that will be holding our final project contributions. We won't be directly modifying the branch because we'll likely have merge conflicts when everyone is trying to apply changes and patches directly. It will be a major headache.

Instead, while you've checkout out the main `matianc-finalproject-bugs` branch, create a new branch on top of this:

`git checkout -b yourname-finalproject-work`

This will create a branch based on the original project branch. You should be contributing and pushing directly to your new branch.

## Git Workflow

Once you've worked and added some code on your individual branch, you first need to stage all of your changes. You can do this easily by using the following command:

`git add .`

You then need to create a commit message. Make a short description of what your changes do:

`git commit -m "My changes did this..."`

Finally, you can push your branch to the remote repository:

`git push origin yourname-finalproject-work`

Down the road, we'll merge our changes into the main project branch and deal with any merge conflicts. I would recommend avoiding any modifications to the dominion files directly. And inside the make file, create individual commands for compiling each unit test.

When we merge everything into the makefile we should have an organized makefile with make commands corresponding to the bug they're compiling and testing:

unittest1: ...
  
unittest2: ...

unittest3: ...

etc.
