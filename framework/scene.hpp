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
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>


struct Scene {

    float ambient_light_ = 0.0f;   //  falls als Elementarsatentyp - nicht als shared pointer, aber falls doch als vec3 bzw. Color datentyp 
    std::shared_ptr<Camera> camera_; // zunaechst als pointer, fuer video sequenz etl auch als liste-mit entsp. pos.-veraenderung
    std::vector<std::shared_ptr<Shape>> shape_list;
    std::vector<std::shared_ptr<Light>> light_list_;
    std::map<std::string,std::shared_ptr<Material>> map_mat;
    std::vector<std::shared_ptr<glm::vec3>> scale_list_;
    std::vector<std::shared_ptr<glm::vec3>> translate_list_;
    std::vector<std::shared_ptr<glm::mat4>> rotate_list_;

};

static void get_SDF_File(std::string const& path,Scene& scene){      // Freie fkt., bekommt
    std::ifstream in_file(path);            // als parameter den dateipfad und oeffnet diesen
    //std::cout << "before while loop in the get_SDF_File method     " << path << std::endl;
    std::string line_buffer;

    while(std::getline(in_file, line_buffer)) {
        std::istringstream current_line_string_stream(line_buffer);
        std::string identifier;
        current_line_string_stream >> identifier;
        //std::cout << "this is in the while-loop of get_SDF_File-method  \n";
        //file.open(path);

        if( "define" == identifier ) {
            //std::cout << "this is if- define  \n";
            current_line_string_stream >> identifier;
            

            if("material" == identifier) {
                //std::cout <<"this is if- material  \n";

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

                Material current_loop_mat{col_as_name,{ka_red,ka_green,ka_blue},{kd_red,kd_green,kd_blue},{ks_red,ks_green,ks_blue},f1};
                auto m1 = std::make_shared<Material>(current_loop_mat);
                //std::cout << current_loop_mat << std::endl;
                scene.map_mat.emplace(col_as_name,m1);

            }
            if("shape" == identifier) {
                //std::cout << "this is if- shape   \n";
                current_line_string_stream >> identifier;                

                if("box" == identifier){
                    //std::cout << "   this is if- box   \n";

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
                    //std::cout << "   this is else if- sphere   \n";
                    
                    std::string sphere_name;
                    current_line_string_stream >> sphere_name;

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
                //std::cout << "this is if light \n";
                
                std::string light_name;
                current_line_string_stream >> light_name;
                    
                Color col_;
                glm::vec3 pos_;
                float luminosity_;

                current_line_string_stream >> pos_.x;
                current_line_string_stream >> pos_.y;
                current_line_string_stream >> pos_.z;

                current_line_string_stream >> col_.r;
                current_line_string_stream >> col_.g;
                current_line_string_stream >> col_.b;

                current_line_string_stream >> luminosity_;

                Light light{light_name,col_, pos_, luminosity_};
                scene.light_list_.push_back(std::make_shared<Light>(light));
                
            }
            if("camera" == identifier) {
                //std::cout << "this is if camera  \n";

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
                //std::cout << "this is if ambient  \n";
            
                current_line_string_stream >> scene.ambient_light_;
              
            }
        }                  
        if("transform" == identifier) {
            std::cout << "this is if transform  \n";

            std::string shape_to_manipul;
            current_line_string_stream >> shape_to_manipul;

            auto it_trans = scene.shape_list.begin();

            for (it_trans ; it_trans != scene.shape_list.end(); ++it_trans){
                if((**it_trans).get_name() == shape_to_manipul){
                    std::cout << "My name is : " << (**it_trans).get_name() << "\n";
                 }
            }
            
            current_line_string_stream >> identifier;

            if("scale" == identifier){
              std::cout << "this is if  scale  \n";

                float x;
                float y;
                float z;

                current_line_string_stream >> x;
                current_line_string_stream >> y;
                current_line_string_stream >> z;
            
				//(**it_trans).scale(x,y,z);

                std::cout<< "after scaling << " << (**it_trans).get_name() << " \n";

            }

            

        } 

        if("render" == identifier) {
                current_line_string_stream >> identifier;
                std::cout << "this is if  render  \n";
        }        
    }
    in_file.close();

    std::cout << "\nFollowing Contents from sdf are saved in this scene : \n";

    std::cout << "map_mat : \n";
    for (auto it_map = scene.map_mat.begin(); it_map != scene.map_mat.end(); ++it_map){   
    std::cout << it_map->first << " => " << *(it_map->second) << '\n';  // erst zugriff auf second, dann erst dereferenzieren !
    }
    std::cout << "shape_list vector : \n";
    for (auto it_vec_1 = scene.shape_list.begin() ; it_vec_1 != scene.shape_list.end(); ++it_vec_1){
    std::cout << **it_vec_1 << "\n";  // doppelt dereferenzieren, weil iterator und smartptr
    }
    std::cout << "light_list vector : \n";
    for (auto it_vec_2 = scene.light_list_.begin() ; it_vec_2 != scene.light_list_.end(); ++it_vec_2)
    std::cout << **it_vec_2 << "\n";  // doppelt dereferenzieren, weil iterator und smartptr
 
    std::cout << "ambient_light_ :\n " << scene.ambient_light_ << "\n";

    std::cout << "camera_ : \n" << *scene.camera_ << "\n";
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