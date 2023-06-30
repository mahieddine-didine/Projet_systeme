from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

 

    solar_system_param = PathJoinSubstitution(

        [

            FindPackageShare("mas_solarsystem"),

            "cfg",

            "solar_system_param.yaml"

        ]

    )

 

    sun_node = Node(

        package="mas_solarsystem",

        executable="celestial_body_node",

        name="sun_node",

        parameters=[

            solar_system_param

        ],

        remappings=[

            ("/marker", "/sun_marker"),

        ],

        output="screen"

    )
    merc_node = Node(

        package="mas_solarsystem",

        executable="celestial_body_node",

        name="merc_node",

        parameters=[

            solar_system_param

        ],

        remappings=[

            ("/marker", "/mercure_marker"),

        ],

        output="screen"

    )
 

 

    return LaunchDescription([soleil_node, mercure_node])