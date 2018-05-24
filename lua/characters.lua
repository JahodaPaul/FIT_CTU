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
