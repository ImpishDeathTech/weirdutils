-- 
-- weirdutils.lua
-- 
-- Copyright (c) 2022, Christopher Stephen Rafuse
-- All rights reserved.
--
-- BSD 3-Clause (see https://github.com/ImpishDeathTech/weirdutils/blob/master/LICENSE) for details
--

function badargument(argument, funcname, expected, got) 
    if got == nil then
        return 'bad argument #'..tostring(argument).." to '"..funcname.."' ("..expected.." expected)"
    else
        return "bad argument #"..tostring(argument).." to '"..funcname.."' ("..expected.." expected, got "..got..")"
    end
end

function enumerate(from, ...)
    local inp = {...}
    local o   = {}

    if type(from) == 'string' then
        table.insert(inp, 1, from)

        for k, v in pairs(inp) do
            if type(k) == 'number' then
                o[v] = k
            end
        end

        local mt = { 
            sz         = #inp,
            __len      = function(self) return getmetatable(self).sz; end, 
            __name     = 'enum'
        }

        setmetatable(o, mt)
        return o
    elseif type(from) == 'number' then 
        for _, v in pairs(inp) do  
            o[v] = from
            from = from + 1
        end
        
        local mt = { 
            sz         = #inp,
            __len      = function(self) return getmetatable(self).sz; end, 
            __name     = 'enum'
        }

        setmetatable(o, mt)
        return o 
    else
       error(badargument(1, 'enumerate', 'string or number', type(from)), 2)
    end
end

function string.split(target, pattern)
    local t = {}

    if type(target) ~= 'string' then 
        error(badargument(1, 'split', 'string', type(target)), 2)
    elseif pattern ~= nil and type(pattern) ~= 'string' then
        error(badargument(2, 'split', 'string or no value', type(pattern)), 2)
    else
        pattern = "([^"..pattern.."]+)" or "([^%s]+)"
    end

    for s in string.gmatch(target, pattern) do
        table.insert(t, s)
    end
    
    return t 
end

function string.prefix(target, prefix)
    if type(target) ~= 'string' then
        error(badargument(1, 'prefix', 'string', type(target)), 2)
    elseif type(prefix) ~= 'string' then
        error(badargument(2, 'prefix', 'string', type(prefix)), 2)
    else
        return target:sub(1, prefix:len()) == prefix
    end
end

function string.suffix(target, suffix)
    if type(target) ~= 'string' then
        error(badargument(1, 'suffix', 'string', type(target)), 2)
    elseif type(suffix) ~= 'string' then
        error(badargument(2, 'suffix', 'string', type(suffix)), 2)
    else
        return text:sub(-suffix:len()) == suffix
    end
end    

function table.shallowcopy(target)
    local o = {}
    
    if type(target) == 'table' then
        for k, v in pairs(target) do 
            o[k] = v
        end
        return o
    else
        error(badargument(1, 'shallowcopy', 'table', type(target)), 2)
    end

    return nil
end

function table.deepcopy(target)
    local o = {}

    if type(target) == 'table' then
        for k, v in pairs(target) do
            t[k] = table.deepcopy(v)
        end
    else
        o = target
    end
    return o
end

function table.address(target) 
    if type(t) == 'table' then
        return string.split(tostring(target))[2]
    else
        error(badargument(1, 'address', 'table', type(target)), 2)
    end
end

function io.clear()
    os.execute('clear')
end

function io.cls()
    os.execute('cls')
end
