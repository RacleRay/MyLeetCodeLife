print("Hello World!")

-- Comment
--[[
    Comments
--]]


-- ============================================================================
num = 42  -- all number is double

s1 = 'immutable strings'
s2 = "double quotes"
s3 = [[double brace]]

print("string" .. " concat")

global_by_default = 5
-- local explicit_local = io.read()
local explicit_local = 1
print("io input", explicit_local)

ud = nil
-- foo = unknown_name is nil

bool_false = nil or false
bool_true = 0
if (bool_true) then
    print("0 is true")
end


-- ============================================================================

while num < 50 do
    num = num + 1
end
print("num is", num)


if (num > 40) then
    print("over 40")
elseif num < 30 then
    print("blow 30")
else 
    print("emmm")
end


acc_sum = 0
for i = 1, 100, 1 do
    acc_sum = acc_sum + i
end
print("acc_sum is", acc_sum)


n = 3
repeat
    print("repeating")
    n = n - 1
until n == 0

-- ============================================================================
-- Funtions

function fib(n)
    if n < 2 then return 1 end
    return fib(n - 2) + fib(n - 1)
end


function addr(x)
    return function(y) return x + y end
end


function bar(a, b)
    print(a, b)
    return 1, 2, 3
end
x = bar('onlyone')   -- input pad by nil. output is discarded


local g; g = function (x) return math.sin(x) end
local function g(x) return math.cos(x) end


-- ============================================================================
-- Tables
-- hash-lookup dicts that can also be used as lists.

t = {key  = 'value'}
print(t.key)
-- t.newKey = {}

t.key = nil
print(t.key)


u = {['@!#'] = 'qbert', [{}] = 1729, [6.28] = 'tau'}
print(u[6.28])
print(u[{}])  -- nil

for key, val in pairs(u) do
    print(key, val)
end


-- ============================================================================
-- metatable
f1 = {a = 1, b = 2}  -- Represents the fraction a/b.
f2 = {a = 2, b = 3}

-- This would fail:
-- s = f1 + f2

metafraction = {}
function metafraction.__add(f1, f2)
  sum = {}
  sum.b = f1.b * f2.b
  sum.a = f1.a * f2.b + f2.a * f1.b
  return sum
end

setmetatable(f1, metafraction)
setmetatable(f2, metafraction)

s = f1 + f2  -- call __add(f1, f2) on f1's metatable


-- ============================================================================
-- Class-like tables
Dog = {}

function Dog:new()
    newObj = {sound = 'wang'}
    self.__index = self
    return setmetatable(newObj, self)
end
--[[
    newObj = {sound = 'woof'}：创建了一个新的表newObj，并在其中定义了一个键值对。
    键是"sound"，值是字符串'woof'。

    self.__index = self：设置了元表（metatable）的__index字段为self。
    元表用于指定在表中查找不存在的键时的行为。这里将元表的__index字段设置为self，
    表示在当前对象中查找不存在的键时，会继续在Dog类中查找。
--]]

function Dog:makeSound()
    print('Dog says' .. self.sound)
end

dog = Dog:new()
dog = makeSound()  


LoudDog = Dog:new()

function LoudDog:makeSound()
    s = self.sound .. ' '
    print(s .. s .. s)
end

ldog = LoudDog:new()
ldog.makeSound()


-- ============================================================================
-- list
v = {'value1', 'value2', 1.21, 'gigawatts'}
for i = 1, #v do   -- indices start from 1 !!!!!
    print(v[i])
end



-- ============================================================================
-- Modules

-- Suppose the file mod.lua looks like this:
local M = {}

local function sayMyName()
  print('Hrunkner')
end

function M.sayHello()
  print('Why hello there')
  sayMyName()
end

return M

-- Another file can use mod.lua's functionality:
local mod = require('mod')  -- Run the file mod.lua


-- This works because mod here = M in mod.lua:
mod.sayHello()  -- Says hello to Hrunkner.

-- This is wrong; sayMyName only exists in mod.lua:
mod.sayMyName()  -- error



    
