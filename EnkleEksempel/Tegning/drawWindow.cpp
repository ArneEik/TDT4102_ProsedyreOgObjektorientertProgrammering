#include "drawWindow.h"

DrawWindow::DrawWindow()
    : AnimationWindow{}//{30, 30, static_cast<int>(width) + 150, static_cast<int>(height) + 50, "Draw Window"},
    //   fileNameToSave{FileNamePoint, 150, BtnHeight, "Filename"},
    //   SaveBtn{SaveBtnPoint, BtnWidth, BtnHeight, "Save"},
    //   ClearBtn{ClearBtnPoint, BtnWidth, BtnHeight, "Clear"},
    //   EraseBtn{EraseBtnPoint, BtnWidth, BtnHeight, "Erase"},
    //   ChangeColorBtn{ChangeColorBtnPoint, BtnWidth, BtnHeight, "Color"}
{
    add(fileNameToSave);
    add(SaveBtn);
    add(ClearBtn);
    add(EraseBtn);
    //add(ChangeColorBtn);
    add(ChangeColorList);
    add(LoadBtn);
    add(RadiusInput);

    SaveBtn.setCallback(std::bind(&DrawWindow::save, this));
    ClearBtn.setCallback(std::bind(&DrawWindow::clear, this));
    EraseBtn.setCallback(std::bind(&DrawWindow::erase, this));
    //ChangeColorBtn.setCallback(std::bind(&DrawWindow::changeColor, this));
    ChangeColorList.setCallback(std::bind(&DrawWindow::changeColor, this));
    LoadBtn.setCallback(std::bind(&DrawWindow::load, this))
;
    // Initialize grid with zeros
    grid = std::vector<std::vector<int>>(height / pixelSize, std::vector<int>(width / pixelSize, 0));
}

void DrawWindow::run() {
    while (!should_close()) {
        draw();
        next_frame();
    }
}

void DrawWindow::draw() {


    for (unsigned int y = 0; y < height / pixelSize; ++y) {
        for (unsigned int x = 0; x < width / pixelSize; ++x) {
            Point topLeftCorner = {static_cast<int>(x * pixelSize), static_cast<int>(y * pixelSize)};
            draw_rectangle(topLeftCorner, static_cast<int>(pixelSize), static_cast<int>(pixelSize), colorMap[grid[y][x]]);
        }
    }

    if (is_left_mouse_button_down()) {
        Point mousePos = get_mouse_coordinates();
        try
        {
            radius = stoi(RadiusInput.getText());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        // Sjekk om museposisjonen er innenfor noen av knappene eller dropdown-listen
        if (!is_point_in_rect(mousePos, FileNamePoint, fileNameToSave.getWidth(), BtnHeight) &&
            !is_point_in_rect(mousePos, SaveBtnPoint, BtnWidth, BtnHeight) &&
            !is_point_in_rect(mousePos, ClearBtnPoint, BtnWidth, BtnHeight) &&
            !is_point_in_rect(mousePos, EraseBtnPoint, BtnWidth, BtnHeight) &&
            !is_point_in_rect(mousePos, ChangeColorBtnPoint, BtnWidth, BtnHeight) &&
            !is_point_in_rect(mousePos, LoadBtnPoint, BtnWidth, BtnHeight) &&
            !is_point_in_rect(mousePos, ChangeColorBtnPoint,ChangeColorList.getWidth(), ChangeColorList.getHeight())) 
        {
            
            int centerX = mousePos.x / static_cast<int>(pixelSize);
            int centerY = mousePos.y / static_cast<int>(pixelSize);
            
            for (int y = -radius; y <= radius; ++y) {
                for (int x = -radius; x <= radius; ++x) {
                    int gridX = centerX + x;
                    int gridY = centerY + y;

                    // Check if the point is inside the circle
                    if (x * x + y * y <= radius * radius) {
                        if (gridX < static_cast<int>(width / pixelSize) && gridY < static_cast<int>(height / pixelSize)) {
                            grid[gridY][gridX] = currentColorIndex; // Set to the current color index
                            pointsToUpdate.insert({gridX, gridY}); // Add point to update list
                        }
                    }
                }
            }
        }
    }
}

bool DrawWindow::is_point_in_rect(const Point& point, const Point& topLeft, int width, int height) const {
    return point.x >= topLeft.x && point.x <= topLeft.x + width &&
           point.y >= topLeft.y && point.y <= topLeft.y + height;
}


void DrawWindow::save() {
    std::string filename = fileNameToSave.getText();
    if (filename.empty()) {
        return;
    }

    std::ofstream outFile(filename + ".txt");
    if (!outFile) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            outFile << cell << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}

void DrawWindow::load()
{
    std::string filename = fileNameToSave.getText();
    if (filename.empty()) {
        return;
    }
    std::ifstream inFile(filename + ".txt");
    if (!inFile) {
        throw std::out_of_range("Cannot open file: " + filename);
    }
    
    for (auto& row : grid) {
        for (auto& cell : row) {
            inFile >> cell;
        }
    }

    inFile.close();
}


void DrawWindow::clear() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), 0);
    }
}
 
void DrawWindow::erase() {
    currentColorIndex = 0; // Set to eraser color
}

void DrawWindow::changeColor() {
    std::string selectedColor = ChangeColorList.getValue();
    for (const auto& [key, value] : colorMap) {
        if (compareColor(value, stringToColor[selectedColor])) {
            currentColorIndex = key;
            break;
        }
    }
}
bool DrawWindow::compareColor(const TDT4102::Color& lhs, const TDT4102::Color& rhs) {
    return lhs.redChannel == rhs.redChannel && lhs.greenChannel == rhs.greenChannel && lhs.blueChannel == rhs.blueChannel && lhs.alphaChannel == rhs.alphaChannel;
}