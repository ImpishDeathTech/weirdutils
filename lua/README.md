# weirdutils.lua
a module of useful utiliy functions for lua to make life a little easier

# Usage

Either drop the module into an existing project, or place in lua/5.4 directory, and require as usual:

```lua
require('weirdutils')
```

## badargument(narg, funcname, expected, got)
produces a string formatted in the "bad argument #narg to 'funcname' (type expected, got type)" error style

```lua
function add(x, y)
  if type(x) ~= 'number' then
    error(badargument(1, 'add', 'number', type(x)), 2)
  else
    return x + y
  end
end
```

## enumerate(from, ...)
produces an enumerated table. If argument 'from' is a number, it will enumerate from that number

```lua
e = enumerate('a', 'b', 'c', 'd')     -- will produce: { a = 1, b = 2, c = 3, d = 4 }
e = enumerate(0, 'a', 'b', 'c', 'd')  -- will produce: { a = 0, b = 1, c = 2, d = 3 }
e = enumerate(-4, 'a', 'b', 'c', 'd') -- will produce: { a = -4, b = -3, c = -2, d = -1 }
```

## string.split(target, pattern)
produces an array table of the resulting strings

```lua
s = 'my name is mud'
s2 = 'suffix: .WAD'

t = string.split(s)         -- will produce: { 'my', 'name', 'is', 'mud' }
t2 = string.split(s2, ': ') -- will produce: { 'suffix', '.WAD' }
```

## string.prefix(target, prefix)
checks the prefix of the given string, and returns a boolean accordingly

```lua
s = 'object: Vector2'

if string.prefix(s, 'object') then
  -- do something
else
  -- do something else
end
```

## string.suffix(target, suffix)
same as the above, but for suffixes

```lua
s = 'suffix: .WAD'
string.suffix(s, '.WAD') -- will produce: true
```

## table.shallowcopy(target)
preforms a shallow copy of a given table. This **will not** copy subtables, any subtables will be copied as references to the original table's subtables

```lua
t = { 
  mobius        = 'an awseome founder of Heavy Metal/Metal Hurlant Magazine!',
  meaningoflife = 42
  window        = { 
    height = 600,
    width  = 800,
    title  = 'terminal'
   }
}

t2 = table.shallowcopy(t) -- will produce: { mobius = 'an awseome founder of Heavy Metal/Metal Hurlant Magazine!', meaningoflife = 42, window = t.window }
```

## table.deepcopy(target)
preforms a recursive deep copy of a given table. This function is implemented in the absolute most efficiant, simple manner we could devise so far.

If the table contains a metatable, or their subtables contain any metatables or too many subtables, this function will fail with a Stack Overflow error
```lua
t = { 
  mobius        = 'an awseome founder of Heavy Metal/Metal Hurlant Magazine!',
  meaningoflife = 42
  window        = { 
    height = 600,
    width  = 800,
    title  = 'terminal'
   }
}

t2 = table.deepcopy(t) -- will produce: { mobius = 'an awseome founder of Heavy Metal/Metal Hurlant Magazine!', meaningoflife = 42, window = { height = 600, width = 800, title = 'terminal } }
```

## table.address(target)
produces a string containing just the memory address of a table, typically only seen with the tostring() function, without 'table' or `__name` prefixed.

This can also be attained using `string.split(tostring(table), ': ')`, but was provided for the convenience, if you require such a functionality as I do.

```lua
t = { 
  mobius        = 'an awseome founder of Heavy Metal/Metal Hurlant Magazine!',
  meaningoflife = 42
  window        = { 
    height = 600,
    width  = 800,
    title  = 'terminal'
   }
}

addr = table.address(t) -- produces a string akin to '0x563b7a202cc0'
```
# License

This module is free software, as such, you can use, redistribute, and/or modify it under the terms of the BSD 3-Clause license. See [LICENSE](https://github.com/ImpishDeathTech/weirdutils/blob/master/LICENSE) for details.
