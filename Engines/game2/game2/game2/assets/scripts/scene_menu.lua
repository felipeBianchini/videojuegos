scene = {
    sprites = {},
    fonts = {
        [1] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start.ttf", fontSize = 24},
        [2] = {fontId = "press_start_32", filePath = "./assets/fonts/press_start.ttf", fontSize = 32},

    },
    soundEffects = {},
    backgroundMusic = {},
    keys = {
        [1] = {name = "up", key = 119},
        [2] = {name = "down", key = 115},
        [3] = {name = "left", key = 97},
        [4] = {name = "right", key = 100},
    },
    buttons = {
        [1] = {name = "mouse_left_button", button = 1},
    },
    maps = {
        width = 800,
        height = 600
    },
    entities = {
        [1] = {
            components = {
                clickable = {},
                text = {
                    text = "Galaxian",
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
                    position = {x = 50.0, y = 150.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
    },
}