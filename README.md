# sml-compiler

Compiler for Simple (BASIC-like) language for [simpletron computer](https://github.com/medvecky/simpletron).

For more details see [Simpletron README](https://github.com/medvecky/simpletron/blob/main/README.md)

## Description 

sml compiler - compile Simple (Limited BASIC-like language) source code to sml 

([simpletron](https://github.com/medvecky/simpletron) executable format)

## App Setup

### Prerequisites

* Installed [Docker](https://www.docker.com/)

or for local setup:
* Installed [clang](https://clang.llvm.org/)
* Installed [gnu make](https://www.gnu.org/software/make/)
* Installed [ctags](https://github.com/universal-ctags/ctags)

### Build and run Docker

```bash
git clone git://github.com/cpputest/cpputest.git
docker-compose build
./docker-make-tests.sh
./docker-make.sh
./docker-sc.sh
```

Get interactive shell in docker container
```bash
./docker-shell.sh
```

### Build and run local

```bash
git clone git://github.com/cpputest/cpputest.git
./make-tests.sh
make sc
bin/sc
```
## Operation manual

### sc compiler usage

```bash
sc simple_source_file_name [-o sml_file_name]
```

simple_source_file_name - file which contains Simple source code
sml_file_name - file which will contain sml executable code

If the output file is not defined - sml executable will be placed in out.sml

### Simple language description

Simple syntax close to classic BASIC syntax.

Each line starts with line number:
```bash
10 rem set m as max holder
20 input m
30 rem set k as loop counter
40 input k
50 rem set s as step
60 input s
70 rem x - current value
80 input x
90 if x < m goto 110
100 let m = x
110 let k = k - s
120 if k = 0 goto 140
130 goto 80
140 print m
150 end
```

#### rem command

**Example**:
```bash
50 rem this is a remark
```
**Description**:

Any text following the command rem is for documentation purposes only and is
ignored by the compiler.

#### input command

**Example**:
```bash
30 input x
```
**Description**:

Display a question mark to prompt the user to enter an integer. Read that integer
from the keyboard and store the integer in x.

#### let command

**Example**:
```bash
80 let a = ( x + y + z ) / d
```

**Description**:

Assign the value of ( x + y + z ) / d. An arbitrarily complex expression can appear
to the right of the equal sign.
In the current implementation, let can work only with variables. Constants not supported.

#### print command

**Example**:
```bash
10 print w
```

**Description**:

Display the value of w.

#### goto command

**Example**:
```bash
70 goto 45
```

**Description**:

Transfer program control to line 45.

#### if...goto command

**Examples**:
```bash
35 if i = z goto 80
35 if i = 0 goto 80
35 if i < z goto 80
35 if i > z goto 80
```

**Description**:

Compare i and z for equality and transfer program control to line 80 if the condition is true; otherwise, continue execution with the next statement.
Supported variants:
 * i = z - equal to variable
 * i = 0 - equal to zero
 * i < z - less than variable
 * i > z - greated than variable

 In current implementation supported equality to variable or zero.

 less than or greater than variable only.

#### end command

**Example**:
```bash
99 end
```

**Description**:

Terminate program execution.
