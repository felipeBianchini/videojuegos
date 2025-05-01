scene = {
    sprites = {
        [1] = {assetId = "ship", filePath = "./assets/images/ship3.png"},
        [2] = {assetId = "bullet", filePath = "./assets/images/missile2.png"},
        [3] = {assetId = "enemy", filePath = "./assets/images/enemy10.png"},
    },
    backgrounds = {
        [1] = {backgroundId = "background1", filePath = "./assets/backgrounds/background1.png"},
    },
    fonts = {
        [1] = {fontId = "press_start", filePath = "./assets/fonts/press_start.ttf", fontSize = 18},
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
                    health = 10,
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
                    text = "",
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
                circle_collider = {
                    radius = 32,
                    width = 64,
                    heigth = 64
                },
                rigid_body = {
                    velocity = {x = 0, y = 0},
                },
                sprite = {
                    assetId = "enemy",
                    width = 128,
                    heigth = 128,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 200.0, y = 100.0},
                    scale = {x = 0.5, y = 0.5},
                    rotation = 0.0,
                },
                health = {
                    health = 5,
                },
                score = {
                    score = 50,
                },
                type = {
                    type = 3,
                }
            }
        },
    },
}
