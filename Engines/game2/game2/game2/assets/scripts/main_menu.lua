scene = {
    sprites = {},
    animations = {},
    fonts = {
        [1] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start.ttf", fontSize = 24},
        [2] = {fontId = "press_start_32", filePath = "./assets/fonts/press_start.ttf", fontSize = 32},
    },
    soundEffects = {},
    backgroundMusic = {
        [1] = {backgroundMusicId = "background_music", filePath = "./assets/backgroundMusic/option1.wav"}
    },
    keys = {},
    buttons = {
        [1] = {name = "mouse_left_button", button = 1},
    },
    maps = {},
    entities = {
        [1] = {
            components = {
                text = {
                    text = "Galactic Siege",
                    fontId = "press_start_32",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 50.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
        [2] = {
            components = {
                clickable = {},
                script = {
                    path = "./assets/scripts/menu_button_01.lua"
                },
                text = {
                    text = "Level 01",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 250.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
        [3] = {
            components = {
                clickable = {},
                script = {
                    path = "./assets/scripts/menu_button_02.lua"
                },
                text = {
                    text = "Level 02",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 350.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },        
        [4] = {
            components = {
                clickable = {},
                script = {
                    path = "./assets/scripts/menu_button_03.lua"
                },
                text = {
                    text = "Level 03",
                    fontId = "press_start_24",
                    r = 150,
                    g = 150,
                    b = 0,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 450.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
    },
}