
// namespace AIAC{
// class Model3d
// {
//     Model3d() = default;
//     ~Model3d() = default;

    
// };

// class PlyLoader
// {
//     // Callback Function for Vertex
// int vertex_cb(p_ply_argument argument) 
// {
// 	static int index = 0;
// 	long eol;
// 	ply_get_argument_user_data(argument, NULL, &eol);
// 	double temp = ply_get_argument_value(argument);

// 	if( index == 0 )
// 	{
// 		if( leftX > temp)
// 			leftX = temp;
// 		if( rightX < temp)
// 			rightX = temp;
// 	}
// 	if( index == 1 )
// 	{
// 		if( topY < temp)
// 			topY = temp;
// 		if( bottomY > temp)
// 			bottomY = temp;
// 	}
// 	if( index == 2 )
// 	{
// 		if( nearZ > temp)
// 			nearZ = temp;
// 		if( farZ < temp)
// 			farZ = temp;
// 	}
	
// 	vertices[ count_vertex].setter_vertex( index++, temp); 

// 	if (eol) 
// 	{
// 		index = 0;
// 		count_vertex++;
// 	}
// 	return 1;
// }

// // Callback Function for Faces
// int face_cb(p_ply_argument argument) 
// {
// 	long length, value_index;
// 	static int index = 0;
// 	ply_get_argument_property(argument, NULL, &length, &value_index);
// 	double temp;
// 	switch (value_index) 
// 	{
// 		case 0:
// 	        case 1: 
// 			temp = ply_get_argument_value(argument);
// 	        	faces[ count_face].setter_vertex( index++, temp);
//         		break;
// 	        case 2:
// 			temp = ply_get_argument_value(argument);
// 	        	faces[ count_face].setter_vertex( index++, temp);
// 	        	index = 0;
// 	        	count_face++;
//         		break;
// 		default:
// 			break;
//     	}
//     	return 1;
// }

// }
// }
