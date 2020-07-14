# Choices C/C++ From a Compiled POV
C code before and after compiling to help demystify exactly what's going on.

Files compiled with `cc -c main.c`, then analyzed with `objdump -d main.o`.

Notation:

Commented out means removed from object code:

| C/C++ Code | Object Code     |
| :------------- | :------------- |
`// Commented out`       | ~Object Code Removed~       |

Noting where equivilents of C/C++ code starts in object code, that isn't actually there:

| C/C++ Code | Object Code     |
| :------------- | :------------- |
| `if (importantCode)` | `# <if (importantCode)>` |

Noting parts of object code replaced with C/C++ for readability:

| C/C++ Code | Object Code     |
| :------------- | :------------- |
| `x = y + z` | `# x = y + z` |

# The Basics

Basic function.
```c
int main() {
}
```
```yaml
0:  55                     push   %rbp
1:  48 89 e5               mov    %rsp,%rbp
4:  b8 00 00 00 00         mov    $0x0,%eax # Return
9:  5d                     pop    %rbp
x:  c3                     retq
```

Creating and adding objects.
```c
// int main() {
  int x = 0;
  int y = 1;
  int z = 0;
  z = x + y;
  return z;
// }
```
```yaml
4:  c7 45 f4 00 00 00 00   movl   $0x0,-0xc(%rbp)
y:  c7 45 f8 01 00 00 00   movl   $0x1,-0x8(%rbp)
12:  c7 45 fc 00 00 00 00   movl   $0x0,-0x4(%rbp) # Create z
19:  8b 55 f4               mov    -0xc(%rbp),%edx
1c:  8b 45 f8               mov    -0x8(%rbp),%eax
1f:  01 d0                  add    %edx,%eax
21:  89 45 fc               mov    %eax,-0x4(%rbp) # Assign z from a-reg
24:  8b 45 fc               mov    -0x4(%rbp),%eax
```

Basic if/else statement
```c
// int main() {
  // int x = 0;
  // int y = 1;
  // int z = 0;
  if (x == 0)
    z = x + y;
  else
    z = x + y;
  return z;
// }
```
```yaml
# <if (x == 0)>
19:  83 7d f8 00            cmpl   $0x0,-0x8(%rbp) # compare x with 0
1d:  75 0d                  jne    2c <main+0x2c>  # x != 0, skip to 2c
1f:  # z = x + y
2a:  eb 0b                  jmp    37 <main+0x37>  # Assigned value, skip to end
# <else>
2c:  # z = x + y
37:  return
```

Assignments in conditional statements
```c
// int main() {
  // int x = 0;
  // int y = 1;
  // int z = 0;
  if (x == y) z = y;
  if (x = y) z = y;
// }

```
```yaml
# <if (x == y)>
19:  8b 45 f4               mov    -0xc(%rbp),%eax # move x to a-reg
1c:  3b 45 f8               cmp    -0x8(%rbp),%eax # compare y with a-reg
1f:  75 06                  jne    27 <main+0x27>  # y != a-reg, skip to 27
21:    # <z = y>
# <if (x = y)>
27:  8b 45 f8               mov    -0x8(%rbp),%eax # move y to a-reg
2a:  89 45 f4               mov    %eax,-0xc(%rbp) # move a-reg to x
2d:  83 7d f4 00            cmpl   $0x0,-0xc(%rbp) # compare 0 to x
31:  74 06                  je     39 <main+0x39>  # x==0, skip to end
33:    # <z = y>
39:    # return 0
```

Assignment *then* conditional vs assignment *in* conditional (code was identical between these, so always do the second!)
```c
// int main() {
//   int x = 0x7;
//   int y = 0x23;
//   int z = 0x5;
  if (x = y) z = y;
  x = y;
  if (x) z = y;
// } /* main */
```
```yaml
# 4:  c7 45 f4 07 00 00 00   movl   $0x7,-0xc(%rbp)
# b:  c7 45 f8 23 00 00 00   movl   $0x23,-0x8(%rbp)
# 12:  c7 45 fc 05 00 00 00   movl   $0x5,-0x4(%rbp)
19:  8b 45 f8               mov    -0x8(%rbp),%eax # move y to a-reg
1c:  89 45 f4               mov    %eax,-0xc(%rbp) # move a-reg to x
1f:  83 7d f4 00            cmpl   $0x0,-0xc(%rbp) # compare 0 to x
23:  74 06                  je     2b <main+0x2b>  # ==0, skip to next statement
25:    # <z = y>
2b:  8b 45 f8               mov    -0x8(%rbp),%eax # move y to a-reg
2e:  89 45 f4               mov    %eax,-0xc(%rbp) # move a-reg to x
31:  83 7d f4 00            cmpl   $0x0,-0xc(%rbp) # compare 0 to x
35:  74 06                  je     3d <main+0x3d>  # ==0, skip to end
37:    # <z = y>
3d:    # return 0
```

# if/else if vs switches

Though this is a simple example, it shows that if/else if statements will recompute a value each time they nest inward, while switches need only do this once then compare against the computed vlue.

If/else statements
```c
// int main() {
  // int x = 0;
  // int y = 1;
  // int z = 0;
  if (x == 0) z = x + y;
  else if (x == 1) z = x + y;
  else if (x == 2) z = x + y;
  else z = x + y;
  return z;
// }
```
```yaml
# <if (x == 0)>
19:  83 7d f8 00            cmpl   $0x0,-0x8(%rbp) # Compute and compare 0 to x
1d:  75 0d                  jne    2c <main+0x2c>  # x != 0, skip to 2c
1f:    # z=x+y
2a:  eb 31                  jmp    5d <main+0x5d>
# <else if (x == 1)>
2c:  83 7d f8 01            cmpl   $0x1,-0x8(%rbp) # Compute and compare 1 to x
30:  75 0d                  jne    3f <main+0x3f>  # x != 1, skip to 3f
32:    # z=x+y
3d:  eb 1e                  jmp    5d <main+0x5d>
# <else if (x == 2)>
3f:  83 7d f8 02            cmpl   $0x2,-0x8(%rbp) # Compute and compare 2 to x
43:  75 0d                  jne    52 <main+0x52>  # x != 2, skip to 52
45:    # z=x+y
50:  eb 0b                  jmp    5d <main+0x5d>
# <else>
52:    # z=x+y
5d:    # return z
```
Use of x switch identical to the if/else statements in execution

```c
// int main() {
  // int x = 0;
  // int y = 1;
  // int z = 0;
  switch (x) {
   case 0: z = x + y;
    break;
   case 1: z = x + y;
    break;
   case 2: z = x + y;
    break;
   default: z = x + y;
    break;
  }
  return z;
// }
```
```yaml
# <switch (x)>
19:  8b 45 f8               mov    -0x8(%rbp),%eax # Compute and move x into a-reg
1c:  83 f8 01               cmp    $0x1,%eax       # Compare 1 to a-reg
1f:  74 16                  je     37 <main+0x37>  # a-reg == 1, skip to 37
21:  83 f8 02               cmp    $0x2,%eax       # Compare 2 to a-reg
24:  74 1e                  je     44 <main+0x44>  # a-reg == 2, skip to 44
26:  85 c0                  test   %eax,%eax       # [eq. to] compare 0 to a-reg
28:  75 27                  jne    51 <main+0x51>  # a-reg != 0, skip to 51
2a:    # z=x+y <case 0>
35:  eb 26                  jmp    5d <main+0x5d>
37:    # z=x+y <case 1>
42:  eb 19                  jmp    5d <main+0x5d>
44:    # z=x+y <case 2>
4f:  eb 0c                  jmp    5d <main+0x5d>
51:    # z=x+y <default>
5d:    # return
```
Changed first case to check for three, not 0.

```c
// int main() {
  // int x = 0;
  // int y = 1;
  // int z = 0;
  switch (x) {
    case 3: z = x + y;
      break;
    case 1: z = x + y;
      break;
    case 2: z = x + y;
      break;
    default: z = x + y;
      break;
  }
  return z;
// }
```
```yaml
# <switch (x)>
19:  8b 45 f8               mov    -0x8(%rbp),%eax # Compute and Cove into a-reg
1c:  83 f8 02               cmp    $0x2,%eax       # Compare 2 to a-reg
1f:  74 26                  je     47 <main+0x47>  # a-reg == 2, skip to 47
21:  83 f8 03               cmp    $0x3,%eax       # Compare 3 to a-reg
24:  74 07                  je     2d <main+0x2d>  # a-reg == 3, skip to 2d
26:  83 f8 01               cmp    $0x1,%eax       # Compare 1 to a-reg
29:  74 0f                  je     3a <main+0x3a>  # a-reg == 1, skip to 3a
2b:  eb 27                  jmp    54 <main+0x54>  # did not equal any, jump
2d:    # z=x+y; <case 3>
38:  eb 26                  jmp    60 <main+0x60>
3a:    # z=x+y; <case 1>
45:  eb 19                  jmp    60 <main+0x60>
47:    # z=x+y; <case 2>
52:  eb 0c                  jmp    60 <main+0x60>
54:    # z=x+y; <default>
60:    # return z;
```

Returning directly in the case statements.
```c
// int main() {
//   int x = 0;
//   int y = 1;
//   int z = 0;
  switch (x) {
  case 3: return x + y;
    break;
  case 1: return x + y;
    break;
  case 2: return x + y;
    break;
  default: return x + y;
    break;
  }
}
```
```yaml
# <switch (x)>
19:  8b 45 f4               mov    -0xc(%rbp),%eax # Move into a-reg
1c:  83 f8 02               cmp    $0x2,%eax       # Compare 2 to a-reg
1f:  74 20                  je     41 <main+0x41>  # a-reg == 2, skip to 41
21:  83 f8 03               cmp    $0x3,%eax       # Compare 3 to a-reg
24:  74 07                  je     2d <main+0x2d>  # a-reg == 3, skip to 2d
26:  83 f8 01               cmp    $0x1,%eax       # Compare 1 to a-reg
29:  74 0c                  je     37 <main+0x37>  # a-reg == 1, skip to 37
2b:  eb 1e                  jmp    4b <main+0x4b>  # default, jump
2d:    # <store x + y for return>
35:    # Jump to end @ 53
37:    # <store x + y for return>
3f:    # Jump to end @ 53
41:    # <store x + y for return>
35:    # Jump to end @ 53
4b:    # <store x + y for return>
53:    # exit <}>
```
