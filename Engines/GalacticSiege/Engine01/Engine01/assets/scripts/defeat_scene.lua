scene = {
    sprites = {
        [1] = {assetId = "frame", filePath = "./assets/images/menu_frame.png"},
        [2] = {assetId = "button", filePath = "./assets/images/menu_button.png"},
    },
    fonts = {
        [1] = {fontId = "press_start_18", filePath = "./assets/fonts/press_start.ttf", fontSize = 18},
        [2] = {fontId = "press_start_24", filePath = "./assets/fonts/press_start.ttf", fontSize = 24},
        [3] = {fontId = "press_start_32", filePath = "./assets/fonts/press_start.ttf", fontSize = 32},

    },
    backgrounds = {
        [1] = {backgroundId = "background", filePath = "./assets/backgrounds/win_defeat_background.png"},
    },
    soundEffects = {},
    backgroundMusic = {
        [1] = {backgroundMusicId = "background_music", filePath = "./assets/backgroundMusic/menu_music.mp3"},
    },
    keys = {},
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
                sprite = {
                    assetId = "frame",
                    width = 940,
                    heigth = 1080,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 271.0, y = 22.0},
                    scale = {x = 0.7, y = 0.7},
                    rotation = 0.0,
                }
            }
        },
        [3] = {
            components = {
                clickable = {},
                sprite = {
                    assetId = "button",
                    width = 361,
                    heigth = 101,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 419.5, y = 380},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
            }
        },
        [4] = {
            components = {
                clickable = {},
                sprite = {
                    assetId = "button",
                    width = 361,
                    heigth = 101,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 419.5, y = 580},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
            }
        },
        [5] = {
            components = {
                text = {
                    text = "Defeat",
                    fontId = "press_start_32",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 504, y = 60},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
            }
        },
        [6] = {
            components = {
                clickable = {},
                text = {
                    text = "Try again",
                    fontId = "press_start_24",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 487.5, y = 410},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                script = {
                     path = "./assets/scripts/go_to_next_scene.lua",
                },
            }
        },
        [7] = {
            components = {
                clickable = {},
                text = {
                    text = "Back to menu",
                    fontId = "press_start_24",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 456, y = 610},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                script = {
                     path = "./assets/scripts/back_to_main_menu_button.lua",
                },
            }
        },
        [8] = {
            components = {
                text = {
                    text = "Try harder >>>>>:c",
                    fontId = "press_start_18",
                    r = 255,
                    g = 255,
                    b = 255,
                    a = 255
                },
                transform = {
                    position = {x = 438, y = 250},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
    },
}