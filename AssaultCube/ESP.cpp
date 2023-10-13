#include "ESP.h"
#include "Geom.h"
#include <iostream>

bool W2S(Vector3 pos, Vector3& screen, float matrix[16], int windowWidth, int windowHeight) {
    Vector4 clipCoords;
    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
    clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
    clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
    clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

    //if entity is behoind u
    if (clipCoords.w < 0.1f)
        return false;
    Vector3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
    screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
    return true;
}

struct entitylista
{
    EntityBase* actor[31];
};

void ESP::Draw(Font& font) {
   
   
    int* Numerodeplayers = (int*)0x58AC0C;
    entitylista* EntityListByFG = *(entitylista**)0x591FCC;
    EntityBase* LocalPlayer = *(EntityBase**)((uintptr_t)GetModuleHandleA(0) + 0x018AC00);
    float* matrix4x4 = (float*)(0x057DFD0);

    std::cout << "x[" << OpenGl::getRes().x << "]" << std::endl;
    std::cout << "y[" << OpenGl::getRes().y << "]" << std::endl;
    std::cout << "Numerodeplayers[" << *Numerodeplayers << "]" << std::endl;
   

    for (int i = 0; i < *Numerodeplayers - 1; i++)
    {

        if (EntityListByFG != nullptr && EntityListByFG->actor[i] != nullptr) {
    

            if (GetAsyncKeyState(VK_F1))
                LocalPlayer->PlayerPos = { EntityListByFG->actor[i]->PlayerPos.x +2,EntityListByFG->actor[i]->PlayerPos.y,EntityListByFG->actor[i]->PlayerPos.z };
            std::cout << "\n\nPlayer[" << i << "]: " << "INFORMACOES OBTIDAS BY FG:" << std::endl;
            std::cout << "Player PTR[" << EntityListByFG->actor[i] << "]: " << std::endl;
            std::cout << "Player Name[" << EntityListByFG->actor[i]->PlayerName << "]: " << std::endl;
            std::cout << "Health[" << EntityListByFG->actor[i]->Vida << "]: " << std::endl;
            std::cout << "Shield[" << EntityListByFG->actor[i]->Escudo << "]: " << std::endl;
            std::cout << "Pos[" << "X: " << EntityListByFG->actor[i]->PlayerPos.x << " Y: " << EntityListByFG->actor[i]->PlayerPos.y << " Z: " << EntityListByFG->actor[i]->PlayerPos.z << "]: " << std::endl;
            std::cout << "HeadPos[" << "X: " << EntityListByFG->actor[i]->HeadPos.x << " Y: " << EntityListByFG->actor[i]->HeadPos.y << " Z: " << EntityListByFG->actor[i]->HeadPos.z << "]: " << std::endl;

            Vector3 Head = EntityListByFG->actor[i]->HeadPos;
            Vector3 Root = EntityListByFG->actor[i]->PlayerPos;
            Vector3 HeadW2S, RootW2S;
            if (W2S(Head, HeadW2S, matrix4x4, OpenGl::getRes().x, OpenGl::getRes().y) && W2S(Root, RootW2S, matrix4x4, OpenGl::getRes().x, OpenGl::getRes().y))
            {
                float height = RootW2S.y - HeadW2S.y; 
                float width = height / 2.0f; 
                Vector3 InicioDaBox = { HeadW2S.x - width / 2.0f , HeadW2S.y ,0};
           
                Vector3 FimDaBox = { HeadW2S.x + width / 2.0f,HeadW2S.y + height , 0 };
              
            
                std::cout << "ENTROU" << std::endl;

                OpenGl::DrawOutline(HeadW2S.x+4, HeadW2S.y+4, HeadW2S.x-4, HeadW2S.y-4, 1.5f, rgb::cyan);
                OpenGl::DrawLine(OpenGl::getRes().x /2, OpenGl::getRes().y , RootW2S.x, RootW2S.y, 1.5f, rgb::cyan);
                OpenGl::DrawOutline(InicioDaBox.x, InicioDaBox.y, FimDaBox.x, FimDaBox.y, 2.0f, rgb::cyan);
               /// textos 
                float textoX = font.centerText(InicioDaBox.x, width, strlen(EntityListByFG->actor[i]->PlayerName) * 9);
                float textoY = InicioDaBox.y - 0.5f;
                font.Print(textoX, textoY, rgb::yellow, "%s", EntityListByFG->actor[i]->PlayerName);

            }



        }


    }
   

}