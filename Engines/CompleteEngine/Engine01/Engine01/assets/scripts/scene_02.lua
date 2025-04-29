scene = {
    sprites = {
        [1] = {assetId = "ship", filePath = "./assets/images/ship1.png"},
    },
    backgrounds = {
        [1] = {backgroundId = "background3", filePath = "./assets/backgrounds/background3.png"},
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
                    radius = 8,
                    width = 16,
                    heigth = 16
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
                    position = {x = 400.0, y = 300.0},
                    scale = {x = 0.4, y = 0.4},
                    rotation = 0.0,
                },
                health = {
                    health = 5,
                },
                score = {
                    score = 0,
                },
                type = {
                    type = 1,
                }
            }
        },
        [3] = {
            components = {
                clickable = {},
                text = {
                    text = "Score: 100",
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
                }
            }
        }
    },
}