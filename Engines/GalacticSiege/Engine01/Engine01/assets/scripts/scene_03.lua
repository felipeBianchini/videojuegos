scene = {
    sprites = {
        [1] = {assetId = "ship", filePath = "./assets/images/ship3.png"},
        [2] = {assetId = "bullet", filePath = "./assets/images/missile2.png"},
        [3] = {assetId = "enemy1", filePath = "./assets/images/enemy11.png"},
        [4] = {assetId = "enemy2", filePath = "./assets/images/enemy8.png"},
        [5] = {assetId = "enemy3", filePath = "./assets/images/enemy3.png"}, 
        [6] = {assetId = "enemy1projectile", filePath = "./assets/images/enemy1projectile.png"},
        [7] = {assetId = "extraLife", filePath = "./assets/images/life_PU.png"},
        [8] = {assetId = "enemy3projectile", filePath = "./assets/images/enemy3projectile.png"},
        [9] = {assetId = "boss", filePath = "./assets/images/boss2.png"},
        [10] = {assetId = "bossProjectile", filePath = "./assets/images/bossProjectile.png"},
        [11] = {assetId = "nuke", filePath = "./assets/images/nuke_PU.png"},
        [12] = {assetId = "explosion", filePath = "./assets/images/explosion.png"},
        [13] = {assetId = "enemydeath1", filePath = "./assets/images/enemydeath1.png"},
        [14] = {assetId = "enemydeath2", filePath = "./assets/images/enemydeath2.png"},
    },
    backgrounds = {
        [1] = {backgroundId = "background2", filePath = "./assets/backgrounds/background2.png"},
    },
    soundEffects = {
        [1] = {soundEffectId = "player_shoot", filePath = "./assets/soundEffects/player_shoot.mp3"},
        [2] = {soundEffectId = "enemy_death", filePath = "./assets/soundEffects/enemy_death.flac"},
        [3] = {soundEffectId = "powerUp_pickUp", filePath = "./assets/soundEffects/powerUp_pickUp.wav"},
        [4] = {soundEffectId = "explosion", filePath = "./assets/soundEffects/explosion.wav"},
        [5] = {soundEffectId = "bossScream", filePath = "./assets/soundEffects/bossScream.flac"},
        [6] = {soundEffectId = "bossDeath", filePath = "./assets/soundEffects/bossDeath.mp3"},

    },
    backgroundMusic = {
        [1] = {backgroundMusicId = "background_music", filePath = "./assets/backgroundMusic/background_music.mp3"},
    },
    fonts = {
        [1] = {fontId = "press_start", filePath = "./assets/fonts/press_start.ttf", fontSize = 24},
    },
    keys = {
        [1] = {name = "up", key = 119},
        [2] = {name = "down", key = 115},
        [3] = {name = "left", key = 97},
        [4] = {name = "right", key = 100},
    },
    buttons = {
        [1] = {name = "mouse_left_button", button = 1},
    },
    entities = {
        [1] = {
            components = {
                sprite = {
                    assetId = "background2",
                    width = 1200,
                    heigth = 800,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 0.0, y = 0.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
        [2] = {
            components = {
                circle_collider = {
                    radius = 32,
                    width = 64,
                    heigth = 64
                },
                rigid_body = {
                    velocity = {x = 0, y = 0},
                },
                script = {
                    path = "./assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "ship",
                    width = 128,
                    heigth = 128,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 600.0, y = 600.0},
                    scale = {x = 0.5, y = 0.5},
                    rotation = 0.0,
                },
                health = {
                    health = 10
                },
                score = {
                    score = 0
                },
                type = {
                    type = 1
                }
            }
        },
        [3] = {
            components = {
                clickable = {},
                text = {
                    text = " ",
                    fontId = "press_start",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 960.0, y = 775.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                type = {
                    type = 0
                },
            }
        },
        [4] = {
            components = {
                clickable = {},
                text = {
                    text = " ",
                    fontId = "press_start",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 25.0, y = 775.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                type = {
                    type = -1
                },
            }
        },
        [5] = {
            components = {
                circle_collider = {
                    radius = 100,
                    width = 256,
                    heigth = 256
                },
                rigid_body = {
                    velocity = {x = 0, y = 0},
                },
                script = {
                    path = "./assets/scripts/boss.lua"
                },
                sprite = {
                    assetId = "boss",
                    width = 256,
                    heigth = 256,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 500.0, y = 0.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                health = {
                    health = 40
                },
                score = {
                    score = 500
                },
                type = {
                    type = 7
                }
            }
        },
        [6] = {
            components = {
                script = {
                    path = "./assets/scripts/extraLifeFactory.lua"
                },
            }
        },
        [7] = {
            components = {
                script = {
                    path = "./assets/scripts/nukeFactory.lua"
                },
            }
        },
        [8] = {
            components = {
                clickable = {},
                text = {
                    text = " ",
                    fontId = "press_start",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 825.0, y = 25.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                type = {
                    type = -3
                },
            }
        }
    },
}