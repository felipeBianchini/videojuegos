scene = {
    sprites = {
        [1] = {assetId = "alan", filePath = "./assets/images/enemy_alan.png"},
        [2] = {assetId = "crushingCyclops", filePath = "./assets/images/CrushingCyclops.png"},
        [3] = {assetId = "swampTroll", filePath = "./assets/images/SwampTroll.png"},
        [4] = {assetId = "background", filePath = "./assets/images/background.png"},
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
    maps = {
        width = 2000,
        heigth = 2000
    },
    entities = {
        [1] = {
            components = {
                sprite = {
                    assetId = "background",
                    width = 2000,
                    heigth = 2000,
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
                camera_follow = {},
                circle_collider = {
                    radius = 8,
                    width = 16,
                    heigth = 16
                },
                rigid_body = {
                    is_dynamic = false,
                    is_solid = false,
                    mass = 1,
                },
                script = {
                    path = "./assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "alan",
                    width = 16,
                    heigth = 16,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 400.0, y = 300.0},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                }
            }
        },
        [3] = {
            components = {
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = false,
                    is_solid = false,
                    mass = 1,
                },
                script = {
                    path = "./assets/scripts/enemy_alan.lua"
                },
                sprite = {
                    assetId = "crushingCyclops",
                    width = 16,
                    heigth = 16,
                    src_rect = {x = 16, y = 0},
                },
                transform = {
                    position = {x = 200.0, y = 100.0},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy 01"
                }
            }
        },
        [4] = {
            components = {
                clickable = {},
                text = {
                    text = "Score: 100",
                    fontId = "press_start",
                    r = 150,
                    g = 0,
                    b = 150,
                    a = 255
                },
                transform = {
                    position = {x = 500.0, y = 50.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                }
            }
        },
        [5] = {
            components = {
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },               
                sprite = {
                    assetId = "swampTroll",
                    width = 16,
                    heigth = 16,
                    src_rect = {x = 16, y = 0},
                },
                transform = {
                    position = {x = 100.0, y = 100.0},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "barrier"
                }
            }
        },
        [6] = {
            components = {
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },               
                sprite = {
                    assetId = "swampTroll",
                    width = 16,
                    heigth = 16,
                    src_rect = {x = 16, y = 0},
                },
                transform = {
                    position = {x = 300.0, y = 100.0},
                    scale = {x = 2.0, y = 2.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "barrier"
                }
            }
        }
    },
}