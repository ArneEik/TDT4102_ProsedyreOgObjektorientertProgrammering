#include "AnimationWindow.h"
#include "std_lib_facilities.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"
#include <unordered_set>

struct PointHash {
    std::size_t operator()(const Point& point) const {
        return std::hash<int>()(point.x) ^ std::hash<int>()(point.y);
    }
};
// Samanlikningsfunksjon for Point
struct PointEqual {
    bool operator()(const Point& lhs, const Point& rhs) const {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};
class DrawWindow : public AnimationWindow {
private:
    std::unordered_set<Point, PointHash, PointEqual> pointsToUpdate;
    unsigned int width = 1024;
    unsigned int height = 768;
    unsigned int BtnWidth = 100;
    unsigned int BtnHeight = 30;
    unsigned int pixelSize = 4;
    int radius = 1;

    Point TopLeftBasePoint = {30 , 30};
    Point FileNamePoint = {30, TopLeftBasePoint.y};
    Point SaveBtnPoint = {static_cast<int>(TopLeftBasePoint.x + 2*(BtnWidth + 10)), TopLeftBasePoint.y};
    Point ClearBtnPoint = {static_cast<int>(TopLeftBasePoint.x + 3 * (BtnWidth + 10)), TopLeftBasePoint.y};
    Point EraseBtnPoint = {static_cast<int>(TopLeftBasePoint.x + 4 * (BtnWidth + 10)), TopLeftBasePoint.y};
    Point ChangeColorBtnPoint = {static_cast<int>(TopLeftBasePoint.x + 5 * (BtnWidth + 10)), TopLeftBasePoint.y};
    Point LoadBtnPoint = {static_cast<int>(TopLeftBasePoint.x + 6 * (BtnWidth + 10)), TopLeftBasePoint.y};
    Point RadiusInputPoint = {static_cast<int>(TopLeftBasePoint.x + 7 * (BtnWidth + 10)), TopLeftBasePoint.y};

    std::vector<std::vector<int>> grid;
    TDT4102::Color currentColor = TDT4102::Color::black;
    int currentColorIndex;
    // std::map<int, TDT4102::Color> colorMap;
    std::vector<std::string> options {"black", "red", "blue", "green"};
map<string, TDT4102::Color> stringToColor{
    {"white", TDT4102::Color::white},
    {"black", TDT4102::Color::black},
    {"red", TDT4102::Color::red},
    {"blue", TDT4102::Color::blue},
    {"green", TDT4102::Color::green}
};
map<int, TDT4102::Color> colorMap = {
        {0, TDT4102::Color::white}, // Eraser color
        {1, TDT4102::Color::black},
        {2, TDT4102::Color::red},
        {3, TDT4102::Color::blue},
        {4, TDT4102::Color::green}
    };

    TDT4102::TextInput fileNameToSave{FileNamePoint, (2*BtnWidth), BtnHeight, "Filename"};
    TDT4102::Button SaveBtn{SaveBtnPoint, BtnWidth, BtnHeight, "Save"};
    TDT4102::Button ClearBtn{ClearBtnPoint, BtnWidth, BtnHeight, "Clear"};
    TDT4102::Button EraseBtn{EraseBtnPoint, BtnWidth, BtnHeight, "Erase"};
    TDT4102::Button ChangeColorBtn{ChangeColorBtnPoint, BtnWidth, BtnHeight, "Color"};
    TDT4102::Button LoadBtn{LoadBtnPoint, BtnWidth, BtnHeight, "Load"};
    TDT4102::DropdownList ChangeColorList{ChangeColorBtnPoint,static_cast<int>(BtnWidth),static_cast<int>(BtnHeight),options};
    TDT4102::TextInput RadiusInput{RadiusInputPoint, (BtnWidth), BtnHeight, "1"};
public:
    DrawWindow();
    void run();
    void save();
    void load();
    void clear();
    void erase();
    void changeColor();
    void draw();

    static bool compareColor(const TDT4102::Color& lhs, const TDT4102::Color& rhs);
    bool is_point_in_rect(const Point& point, const Point& topLeft, int width, int height) const;
};
