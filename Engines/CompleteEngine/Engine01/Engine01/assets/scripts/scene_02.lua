scene = {
    sprites = {
        [1] = {assetId = "ship", filePath = "./assets/images/ship4.png"},
        [2] = {assetId = "bullet", filePath = "./assets/images/missile5.png"},
        [3] = {assetId = "enemy1", filePath = "./assets/images/enemy9.png"},
        [4] = {assetId = "enemy2", filePath = "./assets/images/enemy8.png"},
        [5] = {assetId = "enemy3", filePath = "./assets/images/enemy3.png"}, 
        [6] = {assetId = "enemy1projectile", filePath = "./assets/images/enemy1projectile.png"},
        [7] = {assetId = "extraLife", filePath = "./assets/images/life_PU.png"},
    },
    backgrounds = {
        [1] = {backgroundId = "background3", filePath = "./assets/backgrounds/background3.png"},
    },
    soundEffects = {
        [1] = {soundEffectId = "player_shoot", filePath = "./assets/soundEffects/player_shoot.mp3"},
        [2] = {soundEffectId = "enemy_death", filePath = "./assets/soundEffects/enemy_death.flac"},
        [3] = {soundEffectId = "powerUp_pickUp", filePath = "./assets/soundEffects/powerUp_pickUp.wav"},
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
                    assetId = "background3",
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
                    position = {x = 600.0, y = 400.0},
                    scale = {x = 0.5, y = 0.5},
                    rotation = 0.0,
                },
                health = {
                    health = 5
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
                    position = {x = 960.0, y = 25.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                type = {
                    type = -2
                },
            }
        },
        [6] = {
            components = {
                script = {
                    path = "./assets/scripts/enemyFactory_enemy1.lua"
                },
            }
        },
        [7] = {
            components = {
                script = {
                    path = "./assets/scripts/enemyFactory_enemy2.lua"
                },
            }
        },
        [8] = {
            components = {
                script = {
                    path = "./assets/scripts/enemyFactory_enemy3.lua"
                },
            }
        },
        [9] = {
            components = {
                script = {
                    path = "./assets/scripts/extraLifeFactory.lua"
                },
            }
        }
    },
}