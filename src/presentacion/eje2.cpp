
// #include "../../include/EasySDL/Window.hpp"
#include "../../include/EasySDL/objects/shape/line/ConstraintLine.hpp"
#include "../../include/EasySDL/objects/shape/line/LineStrip.hpp"
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/Math/types/Complex.hpp"
#include "../../include/Math/types/FourierData.hpp"
#include "../../include/Math/methods/DFT.hpp"
#include "../../include/nlohmann/json.hpp"
#include "../../include/EasySDL/WindowLocal.hpp"
#include <cmath>

EasySDL::WindowLocal *w = new EasySDL::WindowLocal(700, 700, "Presentacion");
EasySDL::LineStrip path(1);
std::vector<std::unique_ptr<EasySDL::ContraintLine>> lines;
std::vector<EasySDL::FourierData> result;

int currentStep;
float deltaTime;
int totalSteps;
float t = 0;
void setup()
{
    // ---------------------------------------------
    std::ifstream archivo("./src/presentacion/albert_einstein.json");

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open())
    {
        std::cerr << "No se pudo abrir el archivo JSON." << std::endl;
    }

    // Leer el archivo JSON y almacenarlo en un objeto
    nlohmann::json datos;
    archivo >> datos;

    //--------------
    std::vector<EasySDL::Complex> data;
    int skip = 4;
    //--------------

    // Ejemplo de recorrer un arreglo JSON
    int contador = 0;
    for (const auto &item : datos["points"])
    {
        if (contador % skip == 0)
        {
            EasySDL::Complex values{
                ((float)item["x"] + (float)datos["move_x"]) * (float)datos["dimesion"] * (float)datos["rotate_x"],
                ((float)item["y"] + (float)datos["move_y"]) * (float)datos["dimesion"] * (float)datos["rotate_y"]};
            data.push_back(values);
        }
        contador++;
    }

    result = EasySDL::DFT::dft(data);
    std::sort(result.begin(), result.end(), [](const EasySDL::FourierData &a, const EasySDL::FourierData &b)
              { return a.amplitude > b.amplitude; });

    archivo.close();
    // ---------------------------------------------
    deltaTime = (2 * M_PI) / result.size();
    totalSteps = static_cast<int>((2.0f * M_PI) / deltaTime);
    for (size_t i = 0; i < result.size(); i++)
    {

        lines.push_back(std::make_unique<EasySDL::ContraintLine>(350, 350, 100, 100, 1, result[i].amplitude));
        lines[i]->setAngle(result[i].phase);
        lines[i]->setup();
    }
    path.setColor(EasySDL::MINT_GREEN_NORMALIZED);
    path.setup();
}

void draw()
{
    for (size_t i = 0; i < lines.size(); i++)
    {

        float step = deltaTime * currentStep;

        float angle = result[i].frecuency * step + result[i].phase;
        lines[i]->setAngle(angle);

        if (i > 0)
        {
            lines[i]->setPosPoint1(lines[i - 1]->getPosPoint2());
            lines[i]->draw(w);
            continue;
        }
        lines[i]->draw(w);
    }
    currentStep = (currentStep + 1) % totalSteps;
    path.addPoint(lines.back()->getPosPoint2());
    path.draw(w);
    t += deltaTime;
    if (t > 2 * M_PI)
    {
        path.clearVertexList();
        t = 0;
    }
}

int main()
{
    w->start(draw, setup);
}
