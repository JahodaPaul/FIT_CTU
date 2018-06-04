default = {
    textureFile = "/usr/share/RG/assets/graphics/objects/characters/zombie.png",
    frameWidth = 100,
    frameHeight = 87,
    frameCount = 1,
    frameTime = 9999,
    rotation = 0,
    Dead = function() end,
    Hurt = function() end
}

zombie = {
    textureFile = "/usr/share/RG/assets/graphics/objects/characters/zombie.png",
    frameWidth = 100,
    frameHeight = 87,
    frameCount = 8,
    frameTime = 40,
    rotation = 180,
    Dead = function() play_sound("hurt1", 50) end,
    Hurt = function() play_sound("hurt1", 50) end,
}

player = {
    textureFile = "/usr/share/RG/assets/graphics/objects/characters/player.png",
    frameWidth = 91,
    frameHeight = 91,
    frameCount = 12,
    frameTime = 40,
    rotation = 0,
    Dead = function() play_sound("hurt1", 50) end,
    Hurt = function() play_sound("hurt1", 50) end,
}

stairs_down = {
    textureFile = "/usr/share/RG/assets/graphics/objects/obstacles/holes/hole_big.png",
    frameWidth = 181,
    frameHeight = 174,
    frameCount = 1,
    frameTime = 999,
    rotation = 0,
}
stairs_up = {
    textureFile = "/usr/share/RG/assets/graphics/objects/obstacles/holes/hole_big.png",
    frameWidth = 181,
    frameHeight = 174,
    frameCount = 1,
    frameTime = 999,
    rotation = 0,
}

shoot = {
    textureFile = "/usr/share/RG/assets/graphics/objects/shot1.png",
    frameWidth = 50,
    frameHeight = 50,
    frameCount = 4,
    frameTime = 50,
    rotation = 0,
}
