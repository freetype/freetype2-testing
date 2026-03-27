import os

def create_cache_seed():
    # Command sequence
    # 1 (LookupFace)
    # 2 (LookupSize) -> 16, 16
    # 4 (ImageLookup) -> 3, 0, 16, 16
    # 6 (CMapLookup) -> 65, 0, 0
    # 9 (Unref)
    commands = bytes([
        1,
        2, 16, 16,
        4, 3, 0, 16, 16,
        6, 65, 0, 0,
        9,
        9
    ])
    
    # Read CMap2.ttf
    try:
        with open("freetype-testing/fuzzing/corpora/truetype/bungeman/CMap2.ttf", "rb") as f:
            ttf_data = f.read()
            
        # Write combined file
        with open("seed_cache.bin", "wb") as f:
            f.write(ttf_data)
            f.write(commands)
            
        print("Created seed_cache.bin")
        
    except FileNotFoundError:
        print("CMap2.ttf not found, creating dummy seed")
        with open("seed_cache.bin", "wb") as f:
            f.write(b"DUMMY_TTF_HEADER" + commands)

if __name__ == "__main__":
    create_cache_seed()
