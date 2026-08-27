struct Position {
    int x;
    int y;
};

class Player {
private:
    Position pos{0, 0};
    Position aiming_at{0, 0};
    int health{100};
    bool shooting{false};
    int ammo{10};

public:
    void move(Position new_pos) {
        pos = new_pos;
    }

    void aim(Position target) {
        aiming_at = target;
    }

    void reload() {
        ammo = 10; // Reset ammo to full capacity
    }
};

