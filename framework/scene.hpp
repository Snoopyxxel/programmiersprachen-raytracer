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

    float ambient_light_ = 0.0f;   //  falls als Elementarsatentyp - nicht als shared pointer, aber falls doch als vec3 bzw. Color datentyp 
    std::shared_ptr<Camera> camera_; // zunaechst als pointer, fuer video sequenz etl auch als liste-mit entsp. pos.-veraenderung
    std::vector<std::shared_ptr<Shape>> shape_list;
    std::vector<std::shared_ptr<Light>> light_list_;
    std::map<std::string,std::shared_ptr<Material>> map_mat;
};

static void get_SDF_File(std::string const& path,Scene& scene){      // Freie fkt., bekommt
    std::ifstream in_file(path);            // als parameter den dateipfad und oeffnet diesen
    std::cout << "before while loop in the get_SDF_File method     " << path << std::endl;
    std::string line_buffer;

    while(std::getline(in_file, line_buffer)) {
        std::istringstream current_line_string_stream(line_buffer);
        std::string identifier;
        current_line_string_stream >> identifier;
        std::cout << "this is in the while-loop of get_SDF_File-method  \n";
        //file.open(path);

        if( "define" == identifier ) {
            std::cout << "this is if- define  \n";
            current_line_string_stream >> identifier;
            

            if("material" == identifier) {
                std::cout <<"this is if- material  \n";

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

                std::cout << col_as_name << ", ";

                std::cout << ka_red << " ";
                std::cout << ka_green << " ";
                std::cout << ka_blue << ", ";

                std::cout << kd_red << " ";
                std::cout << kd_green << " ";
                std::cout << kd_blue << ", ";

                std::cout << ks_red << " ";
                std::cout << ks_green << " ";
                std::cout << ks_blue << ", ";

                std::cout << "\n\n f1 ist : " << f1 << std::endl;

                Material current_loop_mat{col_as_name,{ka_red,ka_green,ka_blue},{kd_red,kd_green,kd_blue},{ks_red,ks_green,ks_blue},f1};
                auto m1 = std::make_shared<Material>(current_loop_mat);
                std::cout << current_loop_mat << std::endl;
                scene.map_mat.emplace(col_as_name,m1);

            }
            if("shape" == identifier) {
                std::cout << "this is if- shape   \n";
                current_line_string_stream >> identifier;                

                if("box" == identifier){
                    std::cout << "   this is if- box   \n";

                    std::string box_name;
                    current_line_string_stream >> box_name;

                    glm::vec3 min;
                    glm::vec3 max;
                    std::string mat;
                    std::shared_ptr<Material> ptr_m;

                    current_line_string_stream >> min.x;
                    current_line_string_stream >> min.y;
                    current_line_string_stream >> min.z;

                    current_line_string_stream >> max.x;
                    current_line_string_stream >> max.y;
                    current_line_string_stream >> max.z;

                    current_line_string_stream >> mat;

                    auto it = scene.map_mat.find(mat);
                    if (it != scene.map_mat.end()){
                      ptr_m = it->second;
                    }

                    Box box{box_name, ptr_m, min, max};
                    scene.shape_list.push_back(std::make_shared<Box>(box));
                    
                }else if("sphere" == identifier){
                    std::cout << "   this is else if- sphere   \n";
                    
                    std::string sphere_name;
                    current_line_string_stream >> identifier;

                    glm::vec3 cen;
                    float rad;
                    std::string mat;
                    std::shared_ptr<Material> ptr_m;

                    current_line_string_stream >> cen.x;
                    current_line_string_stream >> cen.y;
                    current_line_string_stream >> cen.z;

                    current_line_string_stream >> rad;
                    
                    current_line_string_stream >> mat;

                    auto it = scene.map_mat.find(mat);
                    if (it != scene.map_mat.end()){
                      ptr_m = it->second;
                    }

                    Sphere sphere{sphere_name, ptr_m, cen, rad};
                    scene.shape_list.push_back(std::make_shared<Sphere>(sphere));
                    
                }
            }
            if("light" == identifier) {
                std::cout << "this is if light \n";
                
                std::string light_name;
                current_line_string_stream >> light_name;
                    
                Color col_;
                glm::vec3 pos_;
                double luminosity_;

                current_line_string_stream >> pos_.x;
                current_line_string_stream >> pos_.y;
                current_line_string_stream >> pos_.z;

                current_line_string_stream >> col_.r;
                current_line_string_stream >> col_.g;
                current_line_string_stream >> col_.b;

                current_line_string_stream >> luminosity_;

                Light light{light_name, pos_, col_, luminosity_};
                scene.light_list_.push_back(std::make_shared<Light>(light));
                
            }
            if("camera" == identifier) {
                std::cout << "this is if camera  \n";

                std::string camera_name;
                current_line_string_stream >> camera_name;

                glm::vec3 pos;
                glm::vec3 dir;
                glm::vec3 up;
                float f_Of_V;

                current_line_string_stream >> pos.x;
                current_line_string_stream >> pos.y;
                current_line_string_stream >> pos.z;
            
                current_line_string_stream >> dir.x;
                current_line_string_stream >> dir.y;
                current_line_string_stream >> dir.z;
            
                current_line_string_stream >> up.x;
                current_line_string_stream >> up.y;
                current_line_string_stream >> up.z;
            
                current_line_string_stream >> f_Of_V;

                Camera cam{camera_name,pos,dir,up,f_Of_V};
                scene.camera_ = std::make_shared<Camera>(cam);
            }
            if("ambient" == identifier) {
                std::cout << "this is if ambient  \n";
            
                current_line_string_stream >> scene.ambient_light_;
            }
        } 
        if("render" == identifier) {
                current_line_string_stream >> identifier;
                std::cout << "this is if - render  \n";
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
static float get_ambient_light_(Scene& s){
    return s.ambient_light_;
}
static Camera get_camera_(Scene& s){
    return *s.camera_;
}
static void print_light_list_(Scene& s){
    
}
static void print_shape_list (Scene& s){
   
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