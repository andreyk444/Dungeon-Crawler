Depths of Knowledge/
├── BaseEnemy.txt        // File with enemies info
├── CMakeLists.txt        // Main CMake file
├── Controller         // Input handling
│  ├── CMakeLists.txt
│  ├── include/Controller/Controller.h  // Controller header
│  └── source/Controller.cpp     // Controller implementation
├── Dungeon           // Dungeon generation and management
│  ├── CMakeLists.txt
│  ├── include/Dungeon/Dungeon.h    // Dungeon header
│  └── source/dungeon.cpp     // Dungeon implementation
├── Element           // Base class for many objects
│  ├── CMakeLists.txt
│  ├── include/Element/element.h     // Element header
│  └── source/element.cpp      // Element implementation
├── Entity           // Base class for game entities
│  ├── CMakeLists.txt
│  ├── include/Entity/entity.h      // Entity header
│  └── source/entity.cpp     // Entity implementation
├── GameObject         // The base class for all objects on screen
│  ├── CMakeLists.txt
│  ├── include/gameObject/GameObject.h   // GameObject header
│  └── source/gameObject.cpp    // GameObject implementation
├── Game_Download        // Contains needed resources and files for a game
│  ├── Download         // Helper class to download some files
│  │  ├── CMakeLists.txt
│  │  ├── include/Download/download.h    // Download header
│  │  └── source/Download.cpp    // Download implementation
│  ├── Dungeon           // Dungeon content
│  │  ├── map.txt           // Map of the Dungeon
│  │  ├── tileset32.png        // Tileset image
│  │  └── tileset64.png        // Tileset image
│  ├── END_GAME          // End screen resources
│  │  ├── lose.png           // Lose screen image
│  │  └── win.png           // Win screen image
│  ├── Entity           // Game entity data
│  │  ├── BaseEnemy.txt        // File with enemies info
│  │  ├── Character.txt        // Character info file
│  │  ├── DemonEnemy.txt
│  │  ├── KenkuEnemy.txt
│  │  ├── MinotaurEnemy.txt
│  │  ├── MinotaurEnemyB.txt
│  │  ├── MummyEnemy.txt
│  │  └── VampireEnemy.txt
│  ├── Equipment          // Equipment data
│  │  └── Armor.txt         // File with the armor information

