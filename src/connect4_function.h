#include <vector>
#include <cctype>

class game_board {
public:
    game_board(std::size_t width, std::size_t height); //Constructor
    ~game_board() = default; //Destructor
    bool is_full() const;
    bool put_coin(int column, char player);
    bool win(char player) const;
    void print_board() const;

    size_t get_width();
    size_t get_height();

    const std::vector<std::vector<char>> &getField() const;

#ifdef TESTS
public:
#else
    private:
#endif
    int connected_squares(char p, int x, int y, int dx, int dy) const;
    bool check_win(char p, int x, int y) const;
    bool index_check(int x, int y) const;
    std::size_t width;
    std::size_t height;

    std::vector<std::vector<char>> field;
    char won = '\0';
};


//Interface
class players{
public:
    virtual ~players() = default; //Destructor
    virtual int throw_coin() const =0;
    virtual const char& getmName() const =0;
};

class human_player : public players{
public:
    explicit human_player(const char &name); //Constructor
    virtual ~human_player() = default; //Destructor
    virtual int throw_coin() const;
    virtual const char& getmName() const; //Getter to read Name of Human Player

#ifdef TESTS
public:
#else
    private:
#endif
    char mName;
};

class computer_player : public players{
public:
    computer_player(const char &name, game_board* spielfeld); //Constructor
    virtual ~computer_player() = default; //Destructor
    virtual int throw_coin() const;
    virtual const char& getmName() const; //Getter to read Name of Computer Player

#ifdef TESTS
public:
#else
    private:
#endif
    char mName;
    game_board* gameboard;
};

