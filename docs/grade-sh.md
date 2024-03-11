# grade.sh: a bash-based automated grading framework

## Introduction
`grade.sh` is a lightweight grading framework intended to be easy to configure and use.
It has a minimal set of dependencies and has a matching Docker image (coming soon) that 
further reduces initial setup overhead.

`grade.sh` uses the existing CI (continuous integration) environment provided by GitLab
to run a set of automated tests each time a student pushes a new commit.  CI frameworks
are already designed to test code correctness and prevent regressions, so this approach
is easily adapted to the grading of programming assignments.  

Instead of submitting their code once on the due date and waiting anxiously to see if 
their code has a fatal bug, students can submit, and more importantly, iteratively 
improve their code as many times as they want prior to the due date.  This increased
grade transparency facilitates increased student engagement, as the grading process is
no longer a black box that spits out a number.  Students can even run the grading script
interactively, during which a debugger is automatically launched in the case of a failed 
test.

Specifically, the grading script will *force* the student into the debugger when they are 
running the grader interactively and a test fails.  This encourages an incremental coding
approach in which components of the program are completed and tested before moving on to
the next segment.

Because it runs entirely in [the cloud](https://i.redd.it/l4bu591x5syy.jpg), `grade.sh` 
does not require the instructor to download the entire set of student code and execute 
(potentially malicious) student code on their own compier.  `grade.sh` also provides
more flexibility than turn-key grading platforms, and at a much lower cost.

## Setup

### Getting `grade-sh`
To use `grade.sh`, simply fork this repository, or, if you do not have the option to fork
(e.g. creating a new example repo or using a different Git host), you can create an entirely
blank repository and run the following:

```sh
# HTTPS
git remote add upstream https://gitlab.com/classroomcode/grade-sh/grade-sh.git

# SSH
git remote add upstream git@gitlab.com:classroomcode/grade-sh/grade-sh.git
```

Then follow the [syncing instructions](#syncing-changes) to download the latest version of `grade-sh`.

[Configure](#configuring) `grade.sh` and add any input files, unit
tests, or instructor-provided files, and `grade.sh` will automatically run once you
(or a student) runs `git push`.

### Configuring
`grade.sh` is primarily configured using a simple config file, `grade.sh`.
The following options are currently available:

* `main_file` (string), the entry point to the student program - in C++, this is the file containing `main()`
* `language` (string), the programming language used in the assignment (C++, Python, Bash, and Rust currently)
* `enable_static_analysis` (bool), whether student code should be scored with a static analyzer - `mypy` for Python, `cppcheck` for C++, `shellcheck` for Bash, and Rust doesn't need this!
* `enable_format_check` (bool), whether the format of the code should be scored - `black` for Python, `clang-format` for C++, `shfmt` for Bash, and `rustfmt` for Rust.

To set a variable, just use `=`, e.g., `enable_static_analysis=true`.  `grade.sh` contains an 
example configuration and more thorough descriptions of the options.

### Adding tests
`grade.sh` currently supports numerous kinds of automated tests of files and code in student repositories:

Python, Bash, C++, and Rust tests:
* [IO tests](#io-tests) (checking a program's std output given some std input)
* [Argument tests](#arg-tests) (running a program against a variety of argument lists, often used for file io)
* [Unit tests](#unit-tests) (importing/linking to student code to run predicates)
* [Code-style format tests](#style-test), run a code format checker to automatically enforce good code style.

Python, Bash, C++ tests
* [Static analysis](static-test), run static analyzers on the student code, and give points accordinly.

Python only tests (currently, others TODO):
* [CFG tests](#cfg-tests), a simple python-only task of mimicking a CFG by producing it's code
* [doctest tests](#doctest-tests), a python-only execution of any doctests present in the main driver.

Language-independent tests:
* [File existence tests](#file-exist-tests), a test for the existence of files, with appropriate data types.
* [Custom tests](#custom-tests), defined in `bash`

They are automatically "enabled" by merely including the appropriate files in the given sub-directories (below).
They are automatically "disabled" by not including files in those sub-directories.

#### Language specific details
Below, follows details about each particular supported language:

##### Rust
* [ ] TODO 
Assumes the use of Cargo for building, cleaning, and running.

##### C
* [ ] TODO 
Assumes the existence of a `Makefile` specifying two targets:
`program.out` and `unit_tests`.

##### C++
* [ ] TODO 
Assumes the existence of a `Makefile` specifying two targets:
`program.out` and `unit_tests`.

##### Python3
* [ ] TODO 

##### Bash
* [ ] TODO 

#### IO tests
If you'd like to run input-based tests on student code, simply add a file called `<TEST_NAME>_input.txt`
to the `sample_inputs` directory, and a corresponding file called `<TEST_NAME>_output.txt` to the 
`sample_outputs` directory for each input-based test.  The process for scoring each of these tests is 
as follows:

1. The contents of the input file for a given test are redirected (`<`) into the student's program, and 
the output saved to a file.
2. The student output file is compared with the instructor-provided output using a *fuzzy diff*. That is,
an exact match is not required for the student to earn credit for a particular test.  Partial credit is 
awarded based on the similarity of student output and the correct output.  

#### Argument tests (often used for file io)
Include files and argument lists in `arg_tests/` to run the students main file against many different argument options.
Things you specify include:
* `arg_tests/args/*_args.txt` list of arguments, one line per file.
* `arg_tests/diffs/` where their diffs between `goals/` and `outputs/` show up.
* `arg_tests/files/*_input.txt` if any file-inputs are specified via argument lists (optional)
* `arg_tests/goals/*_output.txt` desired outputs you specify
* `arg_tests/outputs/` output folder can be populated by file or std-out, depending on how your args are structured.

#### Unit tests
To run tests that operate on small parts (units) of student code instead of their driver, `grade.sh`
provides a set of utility wrappers for all supported languages that minimize the overhead necessary to 
write a test.  Currently, one file corresponds to one unit test.  All unit tests must be in the `unit_tests`
directory.

`stdout` and `stderr` from the unit tests will be displayed to the student when running interactively and as 
part of a CI job, so failure-mode-specific messages can be helpful.

###### Python unit tests
In addition to the root of the repository, the `admin_files` directory should be available to import from.
Python interpreters differ in how they handle import paths, so it may be useful to consult the example Python 
unit tests.

To write a test file, start by importing the test utilities with `import test_utils`.  After importing all
required student files, you can write a test using the provided `test_wrapper` decorator:

```py
@test_utils.test_wrapper
def test() -> bool:
  result = False
  """
  Do stuff with student code here, assigning the test result to
  the "result" variable...
  """
  return result

if __name__ == "__main__":
  test()
```

The test function must always return `bool`.

###### C++ unit tests
If all student code is in the root directory of the repository, no special configuration is needed.  
Currently, this is the only supported location for student code.

To write a test, only a small `main()` function is required:

```cpp
#include "test_utils.hpp"

int main(const int argc, const char **argv)
{
  return test_wrapper(argc, argv, []() {
    bool result = false;
    /**
     * Do stuff with student code here, assigning the test result to
     * the "result" variable...
     */
    return result;
  });
}
```

A lambda is used for uniformity, but other functions can be written and called from within the lambda
as appropriate.  Note that the use of `argc`/`argv` is non-optional, as command-line arguments are used to
ensure that the test is not bypassed by student code.

###### Bash unit tests
No special wrapper is needed for bash unit tests of sourced functions. 
Just source the student file, and return "$1" for a pass, and 1 for a fail.

```sh
#!/bin/bash

source student_file.sh

if [ ! "Test" = "Passed" ]; then
    # For pass
    exit "$1"
else
    # For fail
    exit 1
fi
```

###### Rust unit tests
Just a basic rough draft is done for Rust unit tests. 
TODO:
* decorator
* exception handling


#### Static analysis
Run static analyzers on the student code, and give points accordinly.
Static analyzers supported include:
* Python: `mypy`
* C++: `cppcheck`
* Bash `shellcheck`

#### Code-style format tests
Run a code format checker to automatically enforce good code style.
Auto-formatters supported include:
* Python: `black`
* C++: `clang-format`
* Bash `shfmt`
* Rust `rustfmt`

#### CFG tests
This test is currently python-only, though I'd like to at least extend it to C++ and Rust.
It is a simple task of mimicking a CFG by producing it's code.
This is a low-stakes assignment intended for early in the semester of an introductory programming course.
The workflow looks like this:
1. Instructor programs simple logic (if, for, while, etc) into a little program.
2. Generate cfg from code.
3. Include just the cfg image file in student repo under `cfg_tests/`
4. Student must look at CFG to produce code originally used to generate it.

#### doctest tests
This test is currently python-only, though I'd like to at least extend it to C++ and Rust.
Executes any doctests present in the main driver, and gives points if they all pass, and no points if any fail.
These will be run, if you include `doctest.testmod()` in your main file.

##### File existance and type check tests
In `grade.sh` edit the associative array with filenames and their corresponding data produced with:
```sh
file yourfile.whatever
```

#### Custom tests
If IO and unit tests cannot fully assess student code, you can also add custom tests to `grade.conf`.
Go to the labeled section at the bottom of the file and add one `bash` function per test.  Each function
name should begin with the string `custom_test` and assign their score (integer 0-100) to the variable
`custom_test_score`.  You can call Python scripts or any kind of program in these tests, just remember
to assign to `custom_test_score` at the end of each test.

For example, if for some reason you wanted to grade your students on the ratio of `std::cin` to `std::cout`
in their C++ programs, your custom test might look like the following:

```sh
function custom_test_cin_cout_ratio () {
  student_file="main.cpp"
  cin_ct=$(fgrep -o cin "$student_file" | wc -l)
  cout_ct=$(fgrep -o cout "$student_file" | wc -l)
  custom_test_score=$(python3 -c "print(min(100, int(($cin_ct / $cout_ct) * 100)))")
}
```

## Syncing changes
To update sub-modules in the grade-sh repository itself:
`git submodule update --remote`

If changes are made to `grade.sh` that you would like to incorporate into an existing assignment that uses
`grade.sh`, you should perform the following steps:

1. To make sure that your upstream is configured, run `git remote -v`.  
In addition to the information for your assignment repository (`origin`), you should see the following:
```
upstream        git@gitlab.com:classroomcode/grade-sh/grade-sh.git (fetch)
upstream        git@gitlab.com:classroomcode/grade-sh/grade-sh.git (push)
```

If you do not see this, follow the [setup instructions](#getting-grade-sh) to add the base `grade-sh` repo as a remote.

2. Get the changes with `git fetch upstream`
3. Merge the changes in with `git merge upstream/master`. 
   This may introduce merge conflicts if you have modified certain elements of the `grade.sh` base repo.
