scene = {
    sprites = {
        [1] = {assetId = "player_idle", filePath = "./assets/images/MainCharacters/MaskedMan/player_idle.png"},
        [2] = {assetId = "player_run", filePath = "./assets/images/MainCharacters/MaskedMan/player_run.png"},
        [3] = {assetId = "player_jump", filePath = "./assets/images/MainCharacters/MaskedMan/player_jump.png"},
        [4] = {assetId = "player_fall", filePath = "./assets/images/MainCharacters/MaskedMan/player_fall.png"},
        [5] = {assetId = "tileset", filePath = "./assets/images/tileset2.png"},
        [6] = {assetId = "background", filePath = "./assets/images/Summer3.png"},
        [7] = {assetId = "pig_idle", filePath = "./assets/images/Enemies/AngryPig/pig_idle.png"},
        [8] = {assetId = "pig_walk", filePath = "./assets/images/Enemies/AngryPig/pig_walk.png"},
        [9] = {assetId = "pig_hit", filePath = "./assets/images/Enemies/AngryPig/pig_hit.png"},
        [10] = {assetId = "turtle_idle_spikes_out", filePath = "./assets/images/Enemies/Turtle/turtle_idle_spikes_out.png"},
        [11] = {assetId = "turtle_idle_spikes_in", filePath = "./assets/images/Enemies/Turtle/turtle_idle_spikes_in.png"},
        [12] = {assetId = "turtle_spikes_in", filePath = "./assets/images/Enemies/Turtle/turtle_spikes_in.png"},
        [13] = {assetId = "turtle_spikes_out", filePath = "./assets/images/Enemies/Turtle/turtle_spikes_out.png"},
        [14] = {assetId = "bird_flying", filePath = "./assets/images/Enemies/BlueBird/bird_flying.png"},
        [15] = {assetId = "bird_hit", filePath = "./assets/images/Enemies/BlueBird/bird_hit.png"},
    },
    animations = {
        [1] = {animation_id = "player_idle", texture_id = "player_idle", w = 32, h = 32, num_frames = 11, speed_rate = 15, is_loop = true},
        [2] = {animation_id = "player_run", texture_id = "player_run", w = 32, h = 32, num_frames = 12, speed_rate = 15, is_loop = true},
        [3] = {animation_id = "player_jump", texture_id = "player_jump", w = 32, h = 32, num_frames = 1, speed_rate = 1, is_loop = true},
        [4] = {animation_id = "player_fall", texture_id = "player_fall", w = 32, h = 32, num_frames = 1, speed_rate = 1, is_loop = true},
        [5] = {animation_id = "enemy_pig_idle", texture_id = "pig_idle", w = 36, h = 30, num_frames = 9, speed_rate = 15, is_loop = true},
        [6] = {animation_id = "enemy_pig_walk", texture_id = "pig_walk", w = 36, h = 30, num_frames = 16, speed_rate = 15, is_loop = true},
        [7] = {animation_id = "enemy_pig_hit", texture_id = "pig_hit", w = 36, h = 30, num_frames = 5, speed_rate = 15, is_loop = true},
        [8] = {animation_id = "enemy_turtle_idle_spikes_out", texture_id = "turtle_idle_spikes_out", w = 44, h = 26, num_frames = 14, speed_rate = 14, is_loop = true},
        [9] = {animation_id = "enemy_turtle_idle_spikes_in", texture_id = "turtle_idle_spikes_in", w = 44, h = 26, num_frames = 14, speed_rate = 14, is_loop = true},
        [10] = {animation_id = "enemy_turtle_spikes_in", texture_id = "turtle_spikes_in", w = 44, h = 26, num_frames = 8, speed_rate = 8, is_loop = false},
        [11] = {animation_id = "enemy_turtle_spikes_out", texture_id = "turtle_spikes_out", w = 44, h = 26, num_frames = 8, speed_rate = 8, is_loop = false},
        [12] = {animation_id = "enemy_bird_flying", texture_id = "bird_flying", w = 32, h = 32, num_frames = 9, speed_rate = 9, is_loop = true},
        [13] = {animation_id = "enemy_bird_hit", texture_id = "bird_hit", w = 32, h = 32, num_frames = 5, speed_rate = 5, is_loop = true},

    },
    fonts = {},
    soundEffects = {
        [1] = {soundEffectId = "player_jump", filePath = "./assets/soundEffects/jump.wav"},
        [2] = {soundEffectId = "player_hurt", filePath = "./assets/soundEffects/damage.wav"},
        [3] = {soundEffectId = "boing", filePath = "./assets/soundEffects/boing.flac"},
        [4] = {soundEffectId = "win", filePath = "./assets/soundEffects/win.wav"},
    },
    backgroundMusic = {
        [1] = {backgroundMusicId = "background_music", filePath = "./assets/backgroundMusic/option1.wav"},
    },
    backgrounds = {
        [1] = {
            texture_id = "background",
            w = 2304,
            h = 1296,
            src_x = 0,
            src_y = 0,
            x = 0,
            y = 0,
            scale_x = 5,
            scale_y = 5,
            rotation = 0
        },
    },
    keys = {
        [1] = {name = "up", key = 119},
        [2] = {name = "down", key = 115},
        [3] = {name = "left", key = 97},
        [4] = {name = "right", key = 100},
        [5] = {name = "jump", key = 32},
        [6] = {name = "run", key = 1073742049},
        [7] = {name = "menu", key = 109},
        [8] = {name = "restart", key = 111},
    },
    buttons = {},
    maps = {
        map_path = "./assets/maps/map01/map01.tmx",
        tile_path = "./assets/maps/map01/tileset.tsx",
        tile_name = "tileset"
    },
    entities = {
        [1] = {
            components = {
                animation = {
                    num_frames = 11,
                    speed_rate = 15,
                    is_loop = true,
                },
                camera_follow = {},
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/player.lua"
                },
                sprite = {
                    assetId = "player_idle",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 10.0, y = 2000.0}, -- x = 16.0, y = 3000.0 x = 3200.0, y = 2200.0
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "player",
                },
            }
        },
        [2] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_idle",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 900.0, y = 2900.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [3] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 1100.0, y = 2900.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [4] = {
            components = {
                animation = {
                    num_frames = 15,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 44,
                    heigth = 26,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 1000,
                },
                script = {
                    path = "./assets/scripts/enemy_turtle.lua"
                },
                sprite = {
                    assetId = "turtle_idle_spikes_in",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 625.0, y = 2800.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_turtle",
                },
            }
        },
        [5] = {
            components = {
                animation = {
                    num_frames = 15,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 44,
                    heigth = 26,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 1000,
                },
                script = {
                    path = "./assets/scripts/enemy_turtle.lua"
                },
                sprite = {
                    assetId = "turtle_idle_spikes_out",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 705.0, y = 2800.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_turtle",
                },
            }
        },
        [6] = {
            components = {
                animation = {
                    num_frames = 15,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 44,
                    heigth = 26,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 1000,
                },
                script = {
                    path = "./assets/scripts/enemy_turtle.lua"
                },
                sprite = {
                    assetId = "turtle_idle_spikes_out",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 2000.0, y = 2900.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_turtle",
                },
            }
        },
        [7] = {
            components = {
                animation = {
                    num_frames = 9,
                    speed_rate = 9,
                    is_loop = true,
                },
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/enemy_bird.lua"
                },
                sprite = {
                    assetId = "bird_flying",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 2985.0, y = 2600.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_bird",
                },
            }
        },
       [8] = {
            components = {
                animation = {
                    num_frames = 9,
                    speed_rate = 9,
                    is_loop = true,
                },
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/enemy_bird.lua"
                },
                sprite = {
                    assetId = "bird_flying",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3050.0, y = 2600.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_bird",
                },
            }
        },
        [9] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3400.0, y = 2500.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [10] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3500.0, y = 2500.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [11] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3600.0, y = 2500.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [12] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3700.0, y = 2500.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [13] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3800.0, y = 2500.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [14] = {
            components = {
                animation = {
                    num_frames = 15,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 44,
                    heigth = 26,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 1000,
                },
                script = {
                    path = "./assets/scripts/enemy_turtle.lua"
                },
                sprite = {
                    assetId = "turtle_idle_spikes_out",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3400.0, y = 2300.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_turtle",
                },
            }
        },
       [15] = {
            components = {
                animation = {
                    num_frames = 9,
                    speed_rate = 9,
                    is_loop = true,
                },
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/enemy_bird.lua"
                },
                sprite = {
                    assetId = "bird_flying",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3550.0, y = 2300.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_bird",
                },
            }
        },
       [16] = {
            components = {
                animation = {
                    num_frames = 9,
                    speed_rate = 9,
                    is_loop = true,
                },
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/enemy_bird.lua"
                },
                sprite = {
                    assetId = "bird_flying",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 2975.0, y = 2000.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_bird",
                },
            }
        },
        [17] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 2500.0, y = 2100.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [18] = {
            components = {
                animation = {
                    num_frames = 15,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 44,
                    heigth = 26,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 1000,
                },
                script = {
                    path = "./assets/scripts/enemy_turtle.lua"
                },
                sprite = {
                    assetId = "turtle_idle_spikes_out",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 2500.0, y = 1950.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_turtle",
                },
            }
        },
        [19] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 2600.0, y = 2000.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
        [20] = {
            components = {
                animation = {
                    num_frames = 16,
                    speed_rate = 15,
                    is_loop = true,
                },
                box_collider = {
                    width = 36,
                    heigth = 30,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 100,
                },
                script = {
                    path = "./assets/scripts/enemy_pig.lua"
                },
                sprite = {
                    assetId = "pig_walk",
                    width = 36,
                    heigth = 30,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 2750.0, y = 2000.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_pig",
                },
            }
        },
       [21] = {
            components = {
                animation = {
                    num_frames = 9,
                    speed_rate = 9,
                    is_loop = true,
                },
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/enemy_bird.lua"
                },
                sprite = {
                    assetId = "bird_flying",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3000.0, y = 1900.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_bird",
                },
            }
        },
       [22] = {
            components = {
                animation = {
                    num_frames = 9,
                    speed_rate = 9,
                    is_loop = true,
                },
                box_collider = {
                    width = 32,
                    heigth = 32,
                    offset = {x = 0, y = 0}
                },
                rigid_body = {
                    is_dynamic = true,
                    is_solid = true,
                    mass = 10,
                },
                script = {
                    path = "./assets/scripts/enemy_bird.lua"
                },
                sprite = {
                    assetId = "bird_flying",
                    width = 32,
                    heigth = 32,
                    src_rect = {x = 0, y = 0},
                },
                transform = {
                    position = {x = 3100.0, y = 1900.0},
                    scale = {x = 1.0, y = 1.0},
                    rotation = 0.0,
                },
                tag = {
                    tag = "enemy_bird",
                },
            }
        },
    },
}