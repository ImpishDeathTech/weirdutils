-- 
-- weirdutils.lua
-- 
-- Copyright (c) 2022, Christopher Stephen Rafuse, ImpishDeathTech
-- All rights reserved.
--
-- BSD 3-Clause (see https://github.com/ImpishDeathTech/weirdutils/blob/master/LICENSE) for details
--

function string.badargument(argument, funcname, expected, got) 
    if got == nil then
        return string.format('bad argument #%d to %s (%s expected)', argument, funcname, expected)
    else
        return string.format("bad argument #%d to %s (%s expected, got %s)", argument, funcname, expected, got)
    end
end

function string.eval(text)
    if type(text) == 'string' then
        local func = load(text)
        return pcall(func)
    end
    error(string.badargument(1, 'eval', 'string', type(text)), 2)
end

function string.split(target, pattern)
    local t = {}

    if type(target) ~= 'string' then 
        error(string.badargument(1, 'split', 'string', type(target)), 2)
    elseif pattern ~= nil and type(pattern) ~= 'string' then
        error(string.badargument(2, 'split', 'string or no value', type(pattern)), 2)
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
        error(string.badargument(1, 'prefix', 'string', type(target)), 2)
    elseif type(prefix) ~= 'string' then
        error(string.badargument(2, 'prefix', 'string', type(prefix)), 2)
    else
        return target:sub(1, prefix:len()) == prefix
    end
end

function string.suffix(target, suffix)
    if type(target) ~= 'string' then
        error(string.badargument(1, 'suffix', 'string', type(target)), 2)
    elseif type(suffix) ~= 'string' then
        error(string.badargument(2, 'suffix', 'string', type(suffix)), 2)
    else
        return text:sub(-suffix:len()) == suffix
    end
end

function string.compile(text) 
    if type(text) == 'string' then
        local func = load(text)
        
        if pcall(func) then
            return string.dump(func)
        else
            return 'compile failed'
        end
    else
        error(string.badargument(1, 'compile', 'string', type(text)), 2)
    end
end

function table.shallowcopy(self)
    local o = {}
    
    if type(self) == 'table' then
        for k, v in pairs(self) do 
            o[k] = v
        end
        return o
    else
        error(string.badargument(1, 'shallowcopy', 'table', type(self)), 2)
    end

    return nil
end

function table.deepcopy(self)
    local o = {}

    if type(self) == 'table' then
        for k, v in pairs(self) do
            o[k] = self.deepcopy(v)
        end
    else
        o = self
    end

    return o
end

function table.make(...)
    local o = {...}
    o.shallowcopy = table.shallowcopy
    o.deepcopy    = table.deepcopy
    return o
end

function table.enumerate(from, ...)
    local inp = table.make(...)
    local o   = {}

    o.shallowcopy = table.shallowcopy
    o.deepcopy    = table.deepcopy

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
       error(string.badargument(1, 'enumerate', 'string or number', type(from)), 2)
    end
end

function table.enumerate(from, ...)
    local inp = {...}
    local o   = {}

    o.shallowcopy = table.shallowcopy
    o.deepcopy    = table.deepcopy
    o.address     = table.address

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
       error(string.badargument(1, 'enumerate', 'string or number', type(from)), 2)
    end
end

function io.clear()
    os.execute('clear')
end

function io.compile(path) 
    if type(path) == 'string' then
        local func = loadfile(path)
        
        if pcall(func) then
            return string.dump(func)
        else
            return false
        end
    elseif string.prefix(tostring(path), 'file') then
        local func = load(path:read('a'))
        path:close()

        if pcall(func) then
            return string.dump(func)
        else
            return false
        end
    end
end

function io.cls()
    os.execute('cls')
end
