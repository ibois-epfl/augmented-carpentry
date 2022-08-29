#pragma once



namespace AIAC
{
    class DLoader
    {
    public:
        DLoader() = default;
        ~DLoader() = default;

        bool LoadMesh(const char* path);
    };
}