import rhinoscriptsyntax as rs
import Rhino as rc
import scriptcontext as sc
import Rhino.Geometry as rg

import log



def main():
    log.info(".acim exporter started")
    pieces = rs.GetObjects("Select pieces to be exported", rs.filter.polysurface, preselect=True)
    if not pieces:
        log.error("No pieces selected. Exiting...")
        return

    # create a guid object 3764578b-8b2c-4a98-8c77-348907855bec



    for p_GUID in pieces:
        log.info("Processing piece: " + str(p_GUID))
        log.info("Computing Oriented Bounding Boxes...")

        brep = rs.coercebrep(p_GUID)

        #>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        # PLANE-2-PLANE TRANSFORM

        # find the longest edge of the brep
        edges = brep.Edges
        longest_edge = None
        longest_edge_length = 0
        for edge in edges:
            if edge.GetLength() > longest_edge_length:
                longest_edge_length = edge.GetLength()
                longest_edge = edge
        
        # get face of the longest edge
        face_indices = longest_edge.AdjacentFaces()
        faces = [brep.Faces[face_index] for face_index in face_indices]

        log.info("Found " + str(len(faces)) + " faces for longest edge.")

        # get the biggest face
        biggest_face = None
        biggest_face_area = 0
        for face in faces:
            if rg.AreaMassProperties.Compute(face).Area > biggest_face_area:
                biggest_face_area = rg.AreaMassProperties.Compute(face).Area
                biggest_face = face
        
        # get the plane of the biggest face
        if biggest_face.TryGetPlane()[0] is False:
            log.error("Could not find plane for longest edge. Exiting...")
            return
        plane_src = biggest_face.TryGetPlane()[1]
        log.info("Found plane for longest edge: " + str(plane_src))
        plane_tgt = rc.Geometry.Plane.WorldXY


        # plane to plane transformation
        plane_to_world = rc.Geometry.Transform.PlaneToPlane(plane_src, plane_tgt)

        # transform the brep to the plane
        brep.Transform(plane_to_world)


        #>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        # BBOX

        # compute the bounding box
        bbox = brep.GetBoundingBox(True)
        log.info("Found bounding box: " + str(bbox))

        # convert the bounding box to a brep
        bbox_b = bbox.ToBrep()

        # add the bounding box to the document
        # sc.doc.Objects.AddBrep(bbox_b)

        #>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        # BOOLEAN DIFFERENCE

        # apply a boolean difference between the bbox
        brep_result = rc.Geometry.Brep.CreateBooleanDifference(bbox_b, brep, sc.doc.ModelAbsoluteTolerance)
        if brep_result is None or len(brep_result) == 0:
            log.error("No breps found after boolean difference. Exiting...")
            return

        #>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        # DISTINGUISH BETWEEN HOLE AND SOLID
        # TODO: DEBUG
        holes_b = []
        cuts_b = []

        is_hole = False
        is_cut = False

        for b in brep_result:
            
            is_cut = True
            for f in b.Faces:
                # convert BrepFace to Brep
                f_brep = f.ToBrep()
                # check if the brep is planar
                f = f_brep.Faces[0]

                if not f.IsPlanar():
                    is_hole = True
                    continue


            # for f in b.Faces:
            #     if f.OrientationIsReversed:
            #         holes_b.append(b)
            #         # add the  object with color red
            #         clr_red = rc.Display.Color.Red
            #         rs.ObjectColor(b, clr_red)
            #         sc.doc.Objects.AddBrep(b, clr_red)
            #     else:
            #         cuts_b.append(b)
            
            # change the color of the object to green
            # rs.ObjectColor(b,(255,0,0))


            b_guid = sc.doc.Objects.AddBrep(b)
            CLR_RED = (255,0,0)
            CLR_GREEN = (0,255,0)


            if is_hole:
                rs.ObjectColor(b_guid, CLR_GREEN)
            elif is_cut:
                rs.ObjectColor(b_guid, CLR_RED)

            # rs.ObjectColor(b_guid, CLR_RED)
            # sc.doc.Objects.AddBrep(b)

            sc.doc.Views.Redraw()

            is_hole = False
            is_cut = False



        
    






if __name__ == '__main__':
    main()