#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <set>
#include <map>
#include <memory>
#include <iostream>
#include <string>

#include "Material.hpp"
#include "Shape.hpp"
#include "Box.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "camera.hpp"
#include "light.hpp"

#include <fstream>
#include <sstream>


struct Scene {
    std::vector<std::shared_ptr<Shape>> shape_list;
    float ambient_light_;
    std::vector<std::shared_ptr<Light>> light_list_;
    std::map<std::string,std::shared_ptr<Material>> map_mat;
    std::shared_ptr<Camera> camera_;
};

static void get_SDF_File(std::string const& path,Scene& scene){      // Freie fkt., bekommt
    std::ifstream in_file(path);            // als parameter den dateipfad und oeffnet diesen
    std::cout << "before while loop in the get_SDF_File method     " << path << std::endl;
    std::string line_buffer;

    while(std::getline(in_file, line_buffer)) {
        std::istringstream current_line_string_stream(line_buffer);
        std::string identifier;
        current_line_string_stream >> identifier;

        //file.open(path);

        if( "define" == identifier ) {
            current_line_string_stream >> identifier;

            if("material" == identifier) {
                std::cout << "this is in the while-loop of get_SDF_File-method  \n";

                std::string col_as_name;

                current_line_string_stream >> col_as_name;

                float ka_red, ka_green, ka_blue;
                float kd_red, kd_green, kd_blue;
                float ks_red, ks_green, ks_blue;
                float f1;

                current_line_string_stream >> ka_red;
                current_line_string_stream >> ka_green;
                current_line_string_stream >> ka_blue;

                current_line_string_stream >> kd_red;
                current_line_string_stream >> kd_green;
                current_line_string_stream >> kd_blue;

                current_line_string_stream >> ks_red;
                current_line_string_stream >> ks_green;
                current_line_string_stream >> ks_blue;

                current_line_string_stream >> f1;

                std::cout << col_as_name << std::endl;

                std::cout << ka_red << std::endl;
                std::cout << ka_green << std::endl;
                std::cout << ka_blue << std::endl;

                std::cout << kd_red << std::endl;
                std::cout << kd_green << std::endl;
                std::cout << kd_blue << std::endl;

                std::cout << ks_red << std::endl;
                std::cout << ks_green << std::endl;
                std::cout << ks_blue << std::endl;

                std::cout << f1 << std::endl;

                Material current_loop_mat{col_as_name,{ka_red,ka_green,ka_blue},{kd_red,kd_green,kd_blue},{ks_red,ks_green,ks_blue},f1};
                auto m1 = std::make_shared<Material>(current_loop_mat);
                std::cout << current_loop_mat << std::endl;
                scene.map_mat.emplace(col_as_name,m1);

            }
        }
    }
    in_file.close();
}

static std::shared_ptr<Material> search_map(std::string name, Scene& scene){

    auto it = scene.map_mat.find(name);
    if(it != scene.map_mat.end()){
        return scene.map_mat.find(name)->second;
    }
    else
    {
        return nullptr;
    }
}

static std::shared_ptr<Material> search_vec(std::string name, Scene& scene){
/*
	auto it = scene.vec_mat.find(name);
 	if(it != scene.vec_mat.end()){
 		return scene.vec_mat.find(name)->second;
 	}
 	else
 	{  */
    return nullptr;
    // }

    // Variante 2
/*
 for( std::shared_ptr<Material> m1 : vec_mat){
        if(m1->name_ == s){
            return m;
        }
    }
}
*/
}

static std::shared_ptr<Material> search_set(std::string name, Scene& scene){
    /*
    auto it = scene.set_mat.find(name);
     if(it != scene.set_mat.end()){
         return scene.set_mat.find(name)->second;
     }
     else
     {*/
    return nullptr;
    // }


// Variante 2
    /* for( std::shared_ptr<Material> m1 : set_mat){
          // auto it = set_mat.find(m1);
          if(s == m1->name_){
              return m1;
          }
  } */
}

#endif // SCENE_HPP