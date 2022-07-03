//
// Created by Dennis Wilpert on 03/07/2022.
//

#include "OBJLoader.h"

void OBJLoader::loadOBJ_alt(const std::string & objpath, bool calcnormals, bool calctangents) {
    OBJResult result;

    std::cout << "alt loading" << std::endl;

    try {
        std::ifstream stream(objpath, std::ios_base::in | std::ios_base::binary);
        stream.exceptions(std::ifstream::badbit);
        if (!stream.is_open())
            throw std::logic_error("OBJ file not found.");

        std::string command = "";
        DataCache cache;



        //while(std::getline(stream, line))
        //{

        //}
        while (istreamhelper::peekString(stream, command))
        {
            if (command == "o")
            {
                std::cout << "command: " << command << std::endl;
                //result.objects.push_back(parseObject(cache, stream, calcnormals, calctangents));
            }
            else if (command == "usemtl")
            {
                std::cout << "command: " << command << std::endl;
            }

            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }

        stream.close();


    }catch (const std::exception& ex)
    {
        std::cerr << "Error: Loading OBJ failed: " << ex.what() << "\n";
        throw ex;
    }

    //result.objname = objpath;
    //return result;
}