scene = {
    sprites = {
        [1] = {assetId = "ship", filePath = "./assets/images/ship3.png"},
    },
    backgrounds = {
        [1] = {backgroundId = "background", filePath = "./assets/backgrounds/top_scores_background.png"},
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
                    assetId = "background",
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
                text = {
                    text = "Top Scores",
                    fontId = "press_start",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 50.0, y = 50.0},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                }
            }
        }
    },
}
