Players = {}
Players[0] = { Title = "Squire", Name = "Ciaran", Family = "Wirral", Level = 20 }
Players[1] = { Title = "Lord", Name = "Diego", Family = "Brazil", Level = 50 }

function AddStuff(a, b)
    print("[LUA] AddStuff("..a..", "..b..")")
    return a + b
end

function GetPlayer(n)
    return Players[n]
end

-- HostFunction is defined in C++
function DoAThing(a, b)
    print("[LUA] DoAThing("..a..", "..b..") \n")
    local c = HostFunction(a + 10, b * 3)
    return c
end