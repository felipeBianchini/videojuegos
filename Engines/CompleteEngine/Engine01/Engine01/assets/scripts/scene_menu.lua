scene = {
    sprites = {},
    fonts = {
        [1] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start.ttf", fontSize = 24},
        [2] = {fontId = "press_start_32", filePath = "./assets/fonts/press_start.ttf", fontSize = 32},

    },
    backgrounds = {
        [1] = {backgroundId = "background1", filePath = "./assets/backgrounds/menu_background.png"},
    },
    soundEffects = {},
    backgroundMusic = {
        [1] = {backgroundMusicId = "background_music", filePath = "./assets/backgroundMusic/menu_music.mp3"},
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
                    assetId = "background1",
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
                clickable = {},
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
        [3] = {
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
        [4] = {
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
        [5] = {
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