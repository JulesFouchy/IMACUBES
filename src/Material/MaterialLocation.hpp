#pragma once

struct MaterialLocation {
    int shaderID;
    int materialID;

    MaterialLocation(int shaderID, int materialID)
        : shaderID(shaderID), materialID(materialID) {}

    inline bool isValid() const { return shaderID > -1 && materialID > -1; }
};