"""
    This is a collection of functions to create the filar model of the roof.
"""

import Rhino
import Rhino.Geometry as rg
import scriptcontext as sc

def create_ground_projection(
    ln_sabliereAB,
    ln_sabliereBC,
    ln_sabliereCD,
    ln_sabliereDA,
    offset : float
) -> tuple():
    """
    Create the filar offset of the roof linear model.
    """
    pt_sablereA = ln_sabliereAB.PointAt(0)
    pt_sablereB = ln_sabliereAB.PointAt(1)
    pt_sablereC = ln_sabliereBC.PointAt(1)
    pt_sablereD = ln_sabliereCD.PointAt(1)

    plyln_sabliere = rg.Polyline([pt_sablereA, pt_sablereB, pt_sablereC, pt_sablereD, pt_sablereA])
    crv_sabliere = plyln_sabliere.ToNurbsCurve()
    temp_crv_offset = crv_sabliere.Offset(rg.Plane.WorldXY,
                                          offset,
                                          sc.doc.ModelAbsoluteTolerance,
                                          rg.CurveOffsetCornerStyle.Sharp)[0]
    _, crv_sabliere_offset = temp_crv_offset.TryGetPolyline()

    ln_ground_projectionA1B1 = rg.Line(
        crv_sabliere_offset[0],
        crv_sabliere_offset[1]
    )
    ln_ground_projectionB1C1 = rg.Line(
        crv_sabliere_offset[1],
        crv_sabliere_offset[2]
    )
    ln_ground_projectionC1D1 = rg.Line(
        crv_sabliere_offset[2],
        crv_sabliere_offset[3]
    )
    ln_ground_projectionD1A1 = rg.Line(
        crv_sabliere_offset[3],
        crv_sabliere_offset[0]
    )
    return ln_ground_projectionA1B1, \
        ln_ground_projectionB1C1, \
        ln_ground_projectionC1D1, \
        ln_ground_projectionD1A1

def create_poincon(
    ln_pannerefend_EF : rg.Line,
    ln_pannerefend_FG : rg.Line,
    i_height_faitiere : float
) -> tuple():
    """
    Create the poincon of the roof linear  model.
    """
    pt_pannerefendE = ln_pannerefend_EF.PointAt(0)
    pt_pannerefendF = ln_pannerefend_EF.PointAt(1)
    pt_pannerefendG = ln_pannerefend_FG.PointAt(1)
    pt_poinconE = pt_pannerefendE
    pt_poinconH = rg.Point3d(pt_pannerefendE.X, pt_pannerefendE.Y, i_height_faitiere)
    pt_poinconF = pt_pannerefendF
    pt_poinconI = rg.Point3d(pt_pannerefendF.X, pt_pannerefendF.Y, i_height_faitiere)
    pt_poinconG = pt_pannerefendG
    pt_poinconL = rg.Point3d(pt_pannerefendG.X, pt_pannerefendG.Y, i_height_faitiere)

    ln_poinconEH = rg.Line(pt_poinconE, pt_poinconH)
    ln_poinconFI = rg.Line(pt_poinconF, pt_poinconI)
    ln_poinconGL = rg.Line(pt_poinconG, pt_poinconL)

    return ln_poinconEH, ln_poinconFI, ln_poinconGL

def create_coyer(
    ln_poinconEH : rg.Line,
    ln_poinconGL : rg.Line,
    ln_ground_projectionA1B1 : rg.Line,
    ln_ground_projectionC1D1 : rg.Line,
) -> tuple():
    """
    Create the coyer of the roof linear model.
    """

    pt_poinconE = ln_poinconEH.PointAt(0)
    pt_poinconG = ln_poinconGL.PointAt(0)

    pt_ground_projectionA1 = ln_ground_projectionA1B1.PointAt(0)
    pt_ground_projectionB1 = ln_ground_projectionA1B1.PointAt(1)
    pt_ground_projectionC1 = ln_ground_projectionC1D1.PointAt(0)
    pt_ground_projectionD1 = ln_ground_projectionC1D1.PointAt(1)

    ln_coyerAE = rg.Line(pt_ground_projectionA1, pt_poinconE)
    ln_coyerBG = rg.Line(pt_ground_projectionB1, pt_poinconG)
    ln_coyerCG = rg.Line(pt_ground_projectionC1, pt_poinconG)
    ln_coyerDE = rg.Line(pt_ground_projectionD1, pt_poinconE)

    return ln_coyerAE, ln_coyerBG, ln_coyerCG, ln_coyerDE

def create_arbaletrier_aretier(
    ln_poinconEH : rg.Line,
    ln_poinconGL : rg.Line,
    ln_ground_projectionA1B1 : rg.Line,
    ln_ground_projectionC1D1 : rg.Line
) -> tuple():
    """
    Create the arbaletrier aretier of the roof linear model.
    """
    pt_poinconE = ln_poinconEH.PointAt(0)
    pt_poinconH = ln_poinconEH.PointAt(1)
    pt_poinconG = ln_poinconGL.PointAt(0)
    pt_poinconL = ln_poinconGL.PointAt(1)

    pt_ground_projectionA1 = ln_ground_projectionA1B1.PointAt(0)
    pt_ground_projectionB1 = ln_ground_projectionA1B1.PointAt(1)
    pt_ground_projectionC1 = ln_ground_projectionC1D1.PointAt(0)
    pt_ground_projectionD1 = ln_ground_projectionC1D1.PointAt(1)

    ln_arbaletrier_aretierHA1 = rg.Line(pt_poinconH, pt_ground_projectionA1)
    ln_arbaletrier_aretierLB1 = rg.Line(pt_poinconL, pt_ground_projectionB1)
    ln_arbaletrier_aretierLC1 = rg.Line(pt_poinconL, pt_ground_projectionC1)
    ln_arbaletrier_aretierHD1 = rg.Line(pt_poinconH, pt_ground_projectionD1)

    return ln_arbaletrier_aretierHA1, \
        ln_arbaletrier_aretierLB1, \
        ln_arbaletrier_aretierLC1, \
        ln_arbaletrier_aretierHD1

def create_entrait_fermes(
    ln_poinconEH : rg.Line,
    ln_poinconGL : rg.Line,

    ln_arbaletrier_demi_croupeHM,
    ln_arbaletrier_demi_croupeLN,
) -> tuple():
    """
        Create the entrait fermes of the roof linear model.
    """
    pt_E = ln_poinconEH.PointAt(0)
    pt_G = ln_poinconGL.PointAt(0)

    pt_N = ln_arbaletrier_demi_croupeLN.PointAt(1)
    pt_M = ln_arbaletrier_demi_croupeHM.PointAt(1)

    ln_entrait_fermeEM = rg.Line(pt_E, pt_M)
    ln_entrait_fermeGN = rg.Line(pt_G, pt_N)

    return ln_entrait_fermeEM, ln_entrait_fermeGN

def create_arbaletrier(
    ln_poinconEH : rg.Line,
    ln_poinconFI : rg.Line,
    ln_poinconGL : rg.Line,
    ln_ground_projectionA1B1 : rg.Line,
    ln_ground_projectionC1D1 : rg.Line,
) -> tuple():
    """
    Create the arbaletrier of the roof linear model.
    """
    def calculate_ln_arbaletrier(ln_ground_projection: rg.Line,
                                   pt_base: rg.Point3d) -> rg.Line:
        
        inter_plane = rg.Plane(
            ln_ground_projection.PointAt(0),
            rg.Vector3d(ln_ground_projection.Direction)
        )
        inter_plane.Origin = pt_base

        _, res = rg.Intersect.Intersection.LinePlane(
            ln_ground_projection,
            inter_plane,
            sc.doc.ModelAbsoluteTolerance
        )
        pt_B = ln_ground_projection.PointAt(res)
        ln_arbaletrier = rg.Line(pt_base, pt_B)
        return ln_arbaletrier
    
    pt_E = ln_poinconEH.PointAt(0)
    pt_H = ln_poinconEH.PointAt(1)
    pt_I = ln_poinconFI.PointAt(1)
    pt_F = ln_poinconFI.PointAt(0)
    pt_L = ln_poinconGL.PointAt(1)
    pt_G = ln_poinconGL.PointAt(0)
    
    ln_arbaletrierHT = calculate_ln_arbaletrier(ln_ground_projectionC1D1, pt_H)
    ln_arbaletrierIS = calculate_ln_arbaletrier(ln_ground_projectionC1D1, pt_I)
    ln_arbaletrierLR = calculate_ln_arbaletrier(ln_ground_projectionC1D1, pt_L)

    ln_arbaletrierHO = calculate_ln_arbaletrier(ln_ground_projectionA1B1, pt_H)
    ln_arbaletrierIP = calculate_ln_arbaletrier(ln_ground_projectionA1B1, pt_I)
    ln_arbaletrierLQ = calculate_ln_arbaletrier(ln_ground_projectionA1B1, pt_L)

    return ln_arbaletrierHO, ln_arbaletrierIP, ln_arbaletrierLQ, \
        ln_arbaletrierHT, ln_arbaletrierIS, ln_arbaletrierLR

def create_entrait(
    ln_poinconEH : rg.Line,
    ln_poinconFI : rg.Line,
    ln_poinconGL : rg.Line,

    ln_arbaletrierHO,
    ln_arbaletrierIP,
    ln_arbaletrierLQ,
    ln_arbaletrierHT,
    ln_arbaletrierIS,
    ln_arbaletrierLR,

    ln_ground_projectionA1B1 : rg.Line,
    ln_ground_projectionC1D1 : rg.Line
) -> tuple():
    """
    Create the entrait of the roof linear model.
    """
    
    pt_E = ln_poinconEH.PointAt(0)
    pt_F = ln_poinconFI.PointAt(0)
    pt_G = ln_poinconGL.PointAt(0)

    pt_O = ln_arbaletrierHO.PointAt(1)
    pt_P = ln_arbaletrierIP.PointAt(1)
    pt_Q = ln_arbaletrierLQ.PointAt(1)
    pt_T = ln_arbaletrierHT.PointAt(1)
    pt_S = ln_arbaletrierIS.PointAt(1)
    pt_R = ln_arbaletrierLR.PointAt(1)

    ln_entraitEO = rg.Line(pt_E, pt_O)
    ln_entraitFP = rg.Line(pt_F, pt_P)
    ln_entraitGQ = rg.Line(pt_G, pt_Q)
    ln_entraitET = rg.Line(pt_E, pt_T)
    ln_entraitFS = rg.Line(pt_F, pt_S)
    ln_entraitGR = rg.Line(pt_G, pt_R)

    return ln_entraitEO, ln_entraitFP, ln_entraitGQ, \
        ln_entraitET, ln_entraitFS, ln_entraitGR

def create_arbaletrier_demi_croupe(
    ln_poinconEH : rg.Line,
    ln_poinconGL : rg.Line,
    # ln_entrait_fermeEM : rg.Line,
    # ln_entrait_fermeGN : rg.Line,
    ln_ground_projectionB1C1,
    ln_ground_projectionD1A1
) -> tuple():
    """
    Create the arbaletrier demi croupe of the roof linear model.
    """
    def calculate_ln_arbaletrier_demi_croupe(ln_ground_projection: rg.Line,
                                       pt_base: rg.Point3d) -> rg.Line:
        
        inter_plane = rg.Plane(
            ln_ground_projection.PointAt(0.5),
            rg.Vector3d(ln_ground_projection.Direction)
        )
        inter_plane.Origin = pt_base

        _, res = rg.Intersect.Intersection.LinePlane(
            ln_ground_projection,
            inter_plane,
            sc.doc.ModelAbsoluteTolerance
        )
        pt_B = ln_ground_projection.PointAt(res)
        ln_arbaletrier = rg.Line(pt_base, pt_B)
        
        return ln_arbaletrier

    # pt_M = ln_entrait_fermeEM.PointAt(1)
    pt_H = ln_poinconEH.PointAt(1)

    # pt_N = ln_entrait_fermeGN.PointAt(1)
    pt_L = ln_poinconGL.PointAt(1)

    # ln_arbaletrier_demi_croupeHM = rg.Line(pt_H, pt_M )
    # ln_arbaletrier_demi_croupeLN = rg.Line(pt_L, pt_N)

    ln_arbaletrier_demi_croupeHM = calculate_ln_arbaletrier_demi_croupe(ln_ground_projectionB1C1, pt_L)
    ln_arbaletrier_demi_croupeLN = calculate_ln_arbaletrier_demi_croupe(ln_ground_projectionD1A1, pt_H)

    return ln_arbaletrier_demi_croupeHM, ln_arbaletrier_demi_croupeLN

def create_panne(
    ln_arbaletrierHO : rg.Line,
    ln_arbaletrierIP : rg.Line,
    ln_arbaletrierLQ : rg.Line,
    ln_arbaletrierHT : rg.Line,
    ln_arbaletrierIS : rg.Line,
    ln_arbaletrierLR : rg.Line,
    
    ln_arbaletrier_aretierHA1 : rg.Line,
    ln_arbaletrier_aretierLB1 : rg.Line,
    ln_arbaletrier_aretierLC1 : rg.Line,
    ln_arbaletrier_aretierHD1 : rg.Line,

    ln_arbaletrier_demi_croupeHM : rg.Line,
    ln_arbaletrier_demi_croupeLN : rg.Line,

    i_panne_rawP_position : float,
    i_panne_rawU_position : float
) -> tuple():
    """
    Create the panne of the roof linear model.
    """
    pt_P1 = ln_arbaletrier_aretierHA1.PointAt(i_panne_rawP_position)
    pt_P2 = ln_arbaletrierHO.PointAt(i_panne_rawP_position)
    pt_P3 = ln_arbaletrierIP.PointAt(i_panne_rawP_position)
    pt_P4 = ln_arbaletrierLQ.PointAt(i_panne_rawP_position)
    pt_P5 = ln_arbaletrier_aretierLB1.PointAt(i_panne_rawP_position)
    pt_P6 = ln_arbaletrier_demi_croupeLN.PointAt(i_panne_rawP_position)
    pt_P7 = ln_arbaletrier_aretierLC1.PointAt(i_panne_rawP_position)
    pt_P8 = ln_arbaletrierLR.PointAt(i_panne_rawP_position)
    pt_P9 = ln_arbaletrierIS.PointAt(i_panne_rawP_position)
    pt_P10 = ln_arbaletrierHT.PointAt(i_panne_rawP_position)
    pt_P11 = ln_arbaletrier_aretierHD1.PointAt(i_panne_rawP_position)
    pt_P12 = ln_arbaletrier_demi_croupeHM.PointAt(i_panne_rawP_position)

    pt_U1 = ln_arbaletrier_aretierHA1.PointAt(i_panne_rawU_position)
    pt_U2 = ln_arbaletrierHO.PointAt(i_panne_rawU_position)
    pt_U3 = ln_arbaletrierIP.PointAt(i_panne_rawU_position)
    pt_U4 = ln_arbaletrierLQ.PointAt(i_panne_rawU_position)
    pt_U5 = ln_arbaletrier_aretierLB1.PointAt(i_panne_rawU_position)
    pt_U6 = ln_arbaletrier_demi_croupeLN.PointAt(i_panne_rawU_position)
    pt_U7 = ln_arbaletrier_aretierLC1.PointAt(i_panne_rawU_position)
    pt_U8 = ln_arbaletrierLR.PointAt(i_panne_rawU_position)
    pt_U9 = ln_arbaletrierIS.PointAt(i_panne_rawU_position)
    pt_U10 = ln_arbaletrierHT.PointAt(i_panne_rawU_position)
    pt_U11 = ln_arbaletrier_aretierHD1.PointAt(i_panne_rawU_position)
    pt_U12 = ln_arbaletrier_demi_croupeHM.PointAt(i_panne_rawU_position)

    ln_panneP1P2 = rg.Line(pt_P1, pt_P2)
    ln_panneP2P3 = rg.Line(pt_P2, pt_P3)
    ln_panneP3P4 = rg.Line(pt_P3, pt_P4)
    ln_panneP4P5 = rg.Line(pt_P4, pt_P5)
    ln_panneP5P6 = rg.Line(pt_P5, pt_P6)
    ln_panneP6P7 = rg.Line(pt_P6, pt_P7)
    ln_panneP7P8 = rg.Line(pt_P7, pt_P8)
    ln_panneP8P9 = rg.Line(pt_P8, pt_P9)
    ln_panneP9P10 = rg.Line(pt_P9, pt_P10)
    ln_panneP10P11 = rg.Line(pt_P10, pt_P11)
    ln_panneP11P12 = rg.Line(pt_P11, pt_P12)
    ln_panneP12P1 = rg.Line(pt_P12, pt_P1)

    ln_panneU1U2 = rg.Line(pt_U1, pt_U2)
    ln_panneU2U3 = rg.Line(pt_U2, pt_U3)
    ln_panneU3U4 = rg.Line(pt_U3, pt_U4)
    ln_panneU4U5 = rg.Line(pt_U4, pt_U5)
    ln_panneU5U6 = rg.Line(pt_U5, pt_U6)
    ln_panneU6U7 = rg.Line(pt_U6, pt_U7)
    ln_panneU7U8 = rg.Line(pt_U7, pt_U8)
    ln_panneU8U9 = rg.Line(pt_U8, pt_U9)
    ln_panneU9U10 = rg.Line(pt_U9, pt_U10)
    ln_panneU10U11 = rg.Line(pt_U10, pt_U11)
    ln_panneU11U12 = rg.Line(pt_U11, pt_U12)
    ln_panneU12U1 = rg.Line(pt_U12, pt_U1)

    return ln_panneP1P2, ln_panneP2P3, ln_panneP3P4, ln_panneP4P5, \
        ln_panneP5P6, ln_panneP6P7, ln_panneP7P8, ln_panneP8P9, \
        ln_panneP9P10, ln_panneP10P11, ln_panneP11P12, ln_panneP12P1, \
        ln_panneU1U2, ln_panneU2U3, ln_panneU3U4, ln_panneU4U5, \
        ln_panneU5U6, ln_panneU6U7, ln_panneU7U8, ln_panneU8U9, \
        ln_panneU9U10, ln_panneU10U11, ln_panneU11U12, ln_panneU12U1

def create_enrayure(
    ln_coyerAE : rg.Line,
    ln_coyerBG : rg.Line,
    ln_coyerCG : rg.Line,
    ln_coyerDE : rg.Line,

    ln_entraitGR : rg.Line,
    ln_entraitGQ : rg.Line,
    ln_entraitEO : rg.Line,
    ln_entraitET : rg.Line,
    ln_entrait_fermeGN : rg.Line,
    ln_entrait_fermeEM : rg.Line,

    ln_sabliereAB : rg.Line,
    ln_sabliereBC : rg.Line,
    ln_sabliereCD : rg.Line,
    ln_sabliereDA : rg.Line,

    i_coyer_position : float
) -> tuple():
    """
    Create the enrayure of the roof linear model.
    """
    def _perpendicular_line_typeA(
            pt_extern,
            pt_internal,
            dist,
            sabliereA,
            sabliereB):
        ln = rg.Line(pt_extern, pt_internal)
        pt_enreyure = ln.PointAtLength(dist)
        vec = rg.Vector3d(pt_enreyure - pt_extern)
        plane = rg.Plane(pt_enreyure, vec)
        _, intersect_sabliereA = rg.Intersect.Intersection.LinePlane(
            sabliereA,
            plane,
            sc.doc.ModelAbsoluteTolerance
        )
        A = sabliereA.PointAt(intersect_sabliereA)
        _, intersect_sabliereB = rg.Intersect.Intersection.LinePlane(
            sabliereB,
            plane,
            sc.doc.ModelAbsoluteTolerance
        )
        B = sabliereB.PointAt(intersect_sabliereB)
        ln_enrayureE1E3 = rg.Line(A, B)
        
        return ln_enrayureE1E3

    def _perpendicular_line_typeB(
            pt_extern,
            pt_internal,
            dist,
            entrait_ferme,
            sabliereA,
            sabliereB):
        ln = rg.Line(pt_extern, pt_internal)
        pt_enreyure = ln.PointAtLength(dist)
        vec = rg.Vector3d(pt_enreyure - pt_extern)

        pt_entrait_ferme = entrait_ferme.PointAtLength(dist)
        plane = rg.Plane(pt_entrait_ferme, vec)
        
        _, intersect_sabliereA = rg.Intersect.Intersection.LinePlane(
            sabliereA,
            plane,
            sc.doc.ModelAbsoluteTolerance
        )
        A = sabliereA.PointAt(intersect_sabliereA)
        _, intersect_sabliereB = rg.Intersect.Intersection.LinePlane(
            sabliereB,
            plane,
            sc.doc.ModelAbsoluteTolerance
        )
        B = sabliereB.PointAt(intersect_sabliereB)
        ln_enrayureE1E3 = rg.Line(A, B)
        
        return ln_enrayureE1E3
    
    pt_A = ln_sabliereAB.PointAt(0)
    pt_B = ln_sabliereAB.PointAt(1)
    pt_C = ln_sabliereBC.PointAt(1)
    pt_D = ln_sabliereCD.PointAt(1)
    pt_G = ln_coyerCG.PointAt(1)
    pt_E = ln_coyerAE.PointAt(1)

    ln_enrayureE1E3 = _perpendicular_line_typeA(
        pt_extern=pt_C,
        pt_internal=pt_G,
        dist=i_coyer_position,
        sabliereA=ln_sabliereCD,
        sabliereB=ln_sabliereBC
    )
    ln_enrayureG1G3 = _perpendicular_line_typeA(
        pt_extern=pt_B,
        pt_internal=pt_G,
        dist=i_coyer_position,
        sabliereA=ln_sabliereBC,
        sabliereB=ln_sabliereAB
    )
    ln_enrayureB3B1 = _perpendicular_line_typeA(
        pt_extern=pt_A,
        pt_internal=pt_E,
        dist=i_coyer_position,
        sabliereA=ln_sabliereAB,
        sabliereB=ln_sabliereDA
    )
    ln_enrayureD1D3 = _perpendicular_line_typeA(
        pt_extern=pt_D,
        pt_internal=pt_E,
        dist=i_coyer_position,
        sabliereA=ln_sabliereDA,
        sabliereB=ln_sabliereCD
    )

    ln_enrayureF3F5 = _perpendicular_line_typeB(
        pt_extern=pt_G,
        pt_internal=pt_B,
        entrait_ferme=ln_entrait_fermeGN,
        dist=i_coyer_position,
        sabliereA=ln_entraitGQ,
        sabliereB=ln_entrait_fermeGN
    )
    ln_enrayureF1F3 = _perpendicular_line_typeB(
        pt_extern=pt_G,
        pt_internal=pt_C,
        entrait_ferme=ln_entrait_fermeGN,
        dist=i_coyer_position,
        sabliereA=ln_entraitGR,
        sabliereB=ln_entrait_fermeGN
    )
    ln_enrayureC3C1 = _perpendicular_line_typeB(
        pt_extern=pt_E,
        pt_internal=pt_A,
        entrait_ferme=ln_entrait_fermeEM,
        dist=i_coyer_position,
        sabliereA=ln_entraitEO,
        sabliereB=ln_entrait_fermeEM
    )
    ln_enrayureC1C5 = _perpendicular_line_typeB(
        pt_extern=pt_E,
        pt_internal=pt_D,
        entrait_ferme=ln_entrait_fermeEM,
        dist=i_coyer_position,
        sabliereA=ln_entraitET,
        sabliereB=ln_entrait_fermeEM
    )

    # cut the coyers with the enrayures
    x_coyerAE_ln_enrayureC3C1 = rg.Intersect.Intersection.CurveCurve(
        ln_coyerAE.ToNurbsCurve(),
        ln_enrayureC3C1.ToNurbsCurve(),
        sc.doc.ModelAbsoluteTolerance,
        sc.doc.ModelAbsoluteTolerance
    )
    pt_C2 = x_coyerAE_ln_enrayureC3C1[0].PointA
    x_coyerDE_ln_enrayureC1C5 = rg.Intersect.Intersection.CurveCurve(
        ln_coyerDE.ToNurbsCurve(),
        ln_enrayureC1C5.ToNurbsCurve(),
        sc.doc.ModelAbsoluteTolerance,
        sc.doc.ModelAbsoluteTolerance
    )
    pt_C4 = x_coyerDE_ln_enrayureC1C5[0].PointA
    x_coyerCG_ln_enrayureF1F3 = rg.Intersect.Intersection.CurveCurve(
        ln_coyerCG.ToNurbsCurve(),
        ln_enrayureF1F3.ToNurbsCurve(),
        sc.doc.ModelAbsoluteTolerance,
        sc.doc.ModelAbsoluteTolerance
    )
    pt_F2 = x_coyerCG_ln_enrayureF1F3[0].PointA
    x_coyerBG_ln_enrayureF3F5 = rg.Intersect.Intersection.CurveCurve(
        ln_coyerBG.ToNurbsCurve(),
        ln_enrayureF3F5.ToNurbsCurve(),
        sc.doc.ModelAbsoluteTolerance,
        sc.doc.ModelAbsoluteTolerance
    )
    pt_F4 = x_coyerBG_ln_enrayureF3F5[0].PointA

    ln_coyerAC2 = rg.Line(pt_A, pt_C2)
    ln_coyerBF4 = rg.Line(pt_B, pt_F4)
    ln_coyerCF2 = rg.Line(pt_C, pt_F2)
    ln_coyerDC4 = rg.Line(pt_D, pt_C4)


    return ln_coyerAC2, ln_coyerBF4, ln_coyerCF2, ln_coyerDC4, \
        ln_enrayureE1E3, ln_enrayureF1F3, ln_enrayureF3F5, ln_enrayureG1G3, \
        ln_enrayureC3C1, ln_enrayureB3B1, ln_enrayureD1D3, ln_enrayureC1C5

def create_panne_faitiere(
    ln_poinconEH : rg.Line,
    ln_poinconFI : rg.Line,
    ln_poinconGL : rg.Line
) -> tuple():
    """
    Create the faitiere of the roof linear model.
    """
    pt_H = ln_poinconEH.PointAt(1)
    pt_I = ln_poinconFI.PointAt(1)
    pt_L = ln_poinconGL.PointAt(1)

    ln_faitiereLH = rg.Line(pt_L, pt_H)

    return ln_faitiereLH

def create_jambe_de_force(
    ln_panneP1P2 : rg.Line,
    ln_panneP2P3 : rg.Line,
    ln_panneP3P4 : rg.Line,
    ln_panneP4P5 : rg.Line,
    ln_panneP5P6 : rg.Line,
    ln_panneP6P7 : rg.Line,
    ln_panneP7P8 : rg.Line,
    ln_panneP8P9 : rg.Line,
    ln_panneP9P10 : rg.Line,
    ln_panneP10P11 : rg.Line,
    ln_panneP11P12 : rg.Line,
    ln_panneP12P1 : rg.Line,
    ln_panneU1U2 : rg.Line,
    ln_panneU2U3 : rg.Line,
    ln_panneU3U4 : rg.Line,
    ln_panneU4U5 : rg.Line,
    ln_panneU5U6 : rg.Line,
    ln_panneU6U7 : rg.Line,
    ln_panneU7U8 : rg.Line,
    ln_panneU8U9 : rg.Line,
    ln_panneU9U10 : rg.Line,
    ln_panneU10U11 : rg.Line,
    ln_panneU11U12 : rg.Line,
    ln_panneU12U1 : rg.Line,

    ln_coyerAE : rg.Line,
    ln_coyerBG : rg.Line,
    ln_coyerCG : rg.Line,
    ln_coyerDE : rg.Line,

    ln_entraitEO : rg.Line,
    ln_entraitFP : rg.Line,
    ln_entraitGQ : rg.Line,
    ln_entraitET : rg.Line,
    ln_entraitFS : rg.Line,
    ln_entraitGR : rg.Line,

    ln_entrait_fermeEM : rg.Line,
    ln_entrait_fermeGN : rg.Line,

    i_jambe_de_force_position
) -> tuple():
    """
    Create the jambe de force of the roof linear model.
    """
    ln_jdfP1Y1 = rg.Line(
        ln_panneP1P2.PointAt(0),
        ln_coyerAE.PointAt(1-i_jambe_de_force_position)
    )
    ln_jdfP2Y2 = rg.Line(
        ln_panneP2P3.PointAt(0),
        ln_entraitEO.PointAt(i_jambe_de_force_position)
    )
    ln_jdfP3Y3 = rg.Line(
        ln_panneP3P4.PointAt(0),
        ln_entraitFP.PointAt(i_jambe_de_force_position)
    )
    ln_jdfP4Y4 = rg.Line(
        ln_panneP4P5.PointAt(0),
        ln_entraitGQ.PointAt(i_jambe_de_force_position)
    )
    ln_jdfP5Y5 = rg.Line(
        ln_panneP5P6.PointAt(0),
        ln_coyerBG.PointAt(1-i_jambe_de_force_position)
    )
    ln_jdfP6Y6 = rg.Line(
        ln_panneP6P7.PointAt(0),
        ln_entrait_fermeGN.PointAt(i_jambe_de_force_position)
    )
    ln_jdfP7Y7 = rg.Line(
        ln_panneP7P8.PointAt(0),
        ln_coyerCG.PointAt(1-i_jambe_de_force_position)
    )
    ln_jdfP8Y8 = rg.Line(
        ln_panneP8P9.PointAt(0),
        ln_entraitGR.PointAt(i_jambe_de_force_position)
    )
    ln_jdfP9Y9 = rg.Line(
        ln_panneP9P10.PointAt(0),
        ln_entraitFS.PointAt(i_jambe_de_force_position)
    )
    ln_jdfP10Y10 = rg.Line(
        ln_panneP10P11.PointAt(0),
        ln_entraitET.PointAt(i_jambe_de_force_position)
    )
    ln_jdfP11Y11 = rg.Line(
        ln_panneP11P12.PointAt(0),
        ln_coyerDE.PointAt(1-i_jambe_de_force_position)
    )
    ln_jdfP12Y12 = rg.Line(
        ln_panneP12P1.PointAt(0),
        ln_entrait_fermeEM.PointAt(i_jambe_de_force_position)
    )

    return ln_jdfP1Y1, ln_jdfP2Y2, ln_jdfP3Y3, ln_jdfP4Y4, \
        ln_jdfP5Y5, ln_jdfP6Y6, ln_jdfP7Y7, ln_jdfP8Y8, \
        ln_jdfP9Y9, ln_jdfP10Y10, ln_jdfP11Y11, ln_jdfP12Y12

def create_contre_fiche(
    ln_poinconEH,
    ln_poinconFI,
    ln_poinconGL,

    ln_arbaletrierHO,
    ln_arbaletrierIP,
    ln_arbaletrierLQ,
    ln_arbaletrierHT,
    ln_arbaletrierIS,
    ln_arbaletrierLR,

    ln_arbaletrier_aretierHA1,
    ln_arbaletrier_aretierLB1,
    ln_arbaletrier_aretierLC1,
    ln_arbaletrier_aretierHD1,

    ln_arbaletrier_demi_croupeHM,
    ln_arbaletrier_demi_croupeLN,

    ln_faitiereLH,

    i_dist_joints_poincon
) -> tuple():
    """
    Create the contre fiche of the roof linear model.
    """
    def _ln_diagonal(ln, pt_A, unit_factor, is_flip=False):
        unit_entraitLR = ln.Length / unit_factor
        if is_flip:
            ln.Flip()
        pt_B = ln.PointAtLength(unit_entraitLR)
        ln_ctrfiche = rg.Line(pt_A, pt_B)
        return ln_ctrfiche

    ln_ctrficheK4K5 = None
    ln_ctrficheK4K3 = None
    ln_ctrficheK9K2 = None
    ln_ctrficheK9K6 = None
    ln_ctrficheK7K1 = None
    ln_ctrficheK7K8 = None
    ln_ctrficheZ4Z2 = None
    ln_ctrficheZ4Z3 = None
    ln_ctrficheZ6Z1 = None
    ln_ctrficheZ6Z5 = None
    ln_ctrficheX4X5 = None
    ln_ctrficheX4X3 = None
    ln_ctrficheX6X1 = None
    ln_ctrficheX6X7 = None
    ln_ctrficheX8X2 = None
    ln_ctrficheX8X9 = None

    pt_K7 = ln_poinconGL.PointAtLength(i_dist_joints_poincon)
    pt_K9 = ln_poinconGL.PointAtLength(i_dist_joints_poincon*2)
    pt_K4 = ln_poinconGL.PointAtLength(i_dist_joints_poincon*3)

    ln_ctrficheK9K2 = _ln_diagonal(ln_arbaletrierLR, pt_K9, 4)
    ln_ctrficheK9K6 = _ln_diagonal(ln_arbaletrierLQ, pt_K9, 4)
    ln_ctrficheK4K5 = _ln_diagonal(ln_faitiereLH, pt_K4, 6)
    ln_ctrficheK4K3 = _ln_diagonal(ln_arbaletrier_demi_croupeLN, pt_K4, 5)
    ln_ctrficheK7K1 = _ln_diagonal(ln_arbaletrier_aretierLC1, pt_K7, 3.5)
    ln_ctrficheK7K8 = _ln_diagonal(ln_arbaletrier_aretierLB1, pt_K7, 3.5)

    pt_Z6 = ln_poinconFI.PointAtLength(i_dist_joints_poincon)
    pt_Z4 = ln_poinconFI.PointAtLength(i_dist_joints_poincon*2)

    ln_ctrficheZ4Z3 = _ln_diagonal(ln_faitiereLH, pt_Z4, 3)
    ln_ctrficheZ4Z2 = _ln_diagonal(ln_faitiereLH, pt_Z4, 3, True)
    ln_ctrficheZ6Z1 = _ln_diagonal(ln_arbaletrierIS, pt_Z6, 4)
    ln_ctrficheZ6Z5 = _ln_diagonal(ln_arbaletrierIP, pt_Z6, 4)

    pt_X8 = ln_poinconEH.PointAtLength(i_dist_joints_poincon)
    pt_X6 = ln_poinconEH.PointAtLength(i_dist_joints_poincon*2)
    pt_X4 = ln_poinconEH.PointAtLength(i_dist_joints_poincon*3)

    ln_ctrficheX8X2 = _ln_diagonal(ln_arbaletrier_aretierHD1, pt_X8, 3.5)
    ln_ctrficheX8X9 = _ln_diagonal(ln_arbaletrier_aretierHA1, pt_X8, 3.5)
    ln_ctrficheX6X1 = _ln_diagonal(ln_arbaletrierHT, pt_X6, 4)
    ln_ctrficheX6X7 = _ln_diagonal(ln_arbaletrierHO, pt_X6, 4)
    ln_ctrficheX4X5 = _ln_diagonal(ln_arbaletrier_demi_croupeHM, pt_X4, 5)
    ln_ctrficheX4X3 = _ln_diagonal(ln_faitiereLH, pt_X4, 6)




    return \
        ln_ctrficheK4K5, ln_ctrficheK4K3, \
        ln_ctrficheK9K2, ln_ctrficheK9K6, \
        ln_ctrficheK7K1, ln_ctrficheK7K8, \
        ln_ctrficheZ4Z2, ln_ctrficheZ4Z3, \
        ln_ctrficheZ6Z1, ln_ctrficheZ6Z5, \
        ln_ctrficheX4X5, ln_ctrficheX4X3, \
        ln_ctrficheX6X1, ln_ctrficheX6X7, \
        ln_ctrficheX8X2, ln_ctrficheX8X9

