# General information regarding the autograder, Git, and Gitlab CI/CD pipelines.

## When is this due?
See the Canvas calendar!

## Where to read this file?
This file is nicely displayed in the Gitlab web interface, 
but you can read it locally on your computer too.

## Where to code?
Get your Linux environment set up!
I provide a container and VM configuration scripts for Fedora, 
but you can use any Linux that works.
To use a Linux VM or an OCI/Podman/Docker container, 
see either of the two sub-modiles of this repository, 
the folders `containers/` and `linux_config/`,
depending on which you would like to use.

## How to get this code?
In your Linux enviroment for the class,
find the blue botton that says "clone",
on the home page of this repository.

If you have an ssh key set up:
`git clone --recurse-submodules git@...`

If you don't have an ssh set up, use a token:
`git clone --recurse-submodules https://..`

## How to code?
Let the autograder guide you! 
Using this script, we strongly encourage you to program incrementally. 
It's usually a good idea to do work in the order the autograder checks you.
In general, don't procede to a later function if you are not passing the first one.
If you get stuck, instead of moving on, get help!
See the syllabus for extended coding tips.

## Auto-grader

### How to run the auto-grader on your machine?
Run the following in the root directory of your repository:
```
./grade.sh
# or
bash grade.sh
```
The grader is not intended to be run in WSL/Ubuntu, Mac's zsh terminal, etc.,
but in an actual Linux OS.

## How to run the auto-grader on Gitlab-CI?
Make sure all your files are added, committed, and pushed to the appropriate branch (see Git section below).
Navigate to the Gitlab web interface to confirm these changes exist on the server.

## How to make sure I'm getting points?
* Click on Build -> CI/CD -> Jobs -> the latest job.
* Is it passing, green, etc? 
* What grade does it say you have?
* Whatever grade the latest job says in the terminal output, is what we think you have!

## Std-io tests
Runs your main program, and tests differences between your std-out and the desired std-out
See: `your_diffs/` and `your_outputs` to determine what went wrong. 
We run these diffs automatically, so you may not need to manually inspect these files.

## Arg tests: 
Runs your main program, and tests differences between your file IO with the desired IO.
See: `your_diffs/` and `your_outputs` to determine what went wrong. 
We run these diffs automatically, so you may not need to manually inspect these files.

## Unit tests: we're micromanaging your functions!
See the unit tests themselves, and run them in your favorite debugger:
`unit_tests/`

## Git
Git happens... See this link:
<https://cs-mst.gitlab.io/index/Classes/DataStructuresLab/Content/03-VersionControl.html>

### Submit your work: add, commit, push
Finally, to submit all your work, 
it is time to manage these files you created within your Git repository.
They must all be in the folder created when you cloned your Git repository.
From within your git repository (folder), add, commit, and push all the non-generated files. 
This means add your cpp and py files, for example, but not a.out, etc.
These commands should move your edits to the repository to the git-classes server:
```sh
git add file1
git add file2
# Where you do this for all your source files
git commit -am "Time to git committed to this ;)"
git push -u origin main
```
Read the resulting message Git prints!
Most importantly, to check all your previous Git-related steps worked,
using the web browser, navigate back to the repository,
and confirm all the files you added are visible in the Gitlab web interface.
If the files are not visible,
then you will not be graded for them,
and you should go ask for help!
If you can see the correct files on git-classes in your main branch,
then your push is complete.
Make sure all the requested files are in the root directory of the repository,
unless otherwise specified.

## How to make sure I'm getting points?
To determine whether your project is finished:
Check out the git-classes Gitlab CI (details in the general syllabus). 
If it turns green AND the details show a 100,
then you're good! 
If it's still red or you are less than 100,
then you need to fix your project.
This test checks both that you got your files submitted correctly,
and that your submission was correct!

Click on CI/CD -> Jobs -> the latest job.
What grade does it say you have?
Whatever grade the latest job says,
is what we think you have!

## Errors
You should not change any of the grading files themselves. 
If you do, you will see a warning, and it will give you a 0.
If you accidentally did that:
`git checkout firstfourcharactersoflastcommitbyus graderfileyoubroke`

### Is the auto-grader broken?
Is the error you're encountering our fault or yours?
Either may be possible, while the latter is a bit more likely.
Double-check all the diffs, and step through all code to see.
If you think you found a bug, please let us know!

## grade.sh: this automated grading framework
For more details on the generalized auto-grader, see:
[grade-sh.md](grade-sh.md)

## Improvements
If you notice any issues or improvements, 
please feel free to check out our source repository:
<https://gitlab.com/classroomcode/grade-sh/grade-sh>
