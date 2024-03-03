#! python3

import Rhino
import Rhino.Geometry as rg
import scriptcontext as sc

import Grasshopper as gh

import filar_model as fm

import re


def extract_lbl(dict):
    """
        This is a simple util modules to extract an unique set of points and their labels
        from a dictionary of lines labels.
        The entry dictionnary is as such:
        dict = {
            "AB" : rg.Line,  # with rg.Line.PointAt(0) = A and rg.Line.PointAt(1) = B
            "A12B2" : rg.Line,  # with rg.Line.PointAt(0) = A12 and rg.Line.PointAt(1) = B2
        }
        The return is a dictionary of with the point label and the rg.Point3d
    """
    def parse_string(s):
        return re.findall(r'[A-Za-z]\d*|[A-Za-z]', s)

    dict_pts = {}
    parsed = [parse_string(k) for k in dict.keys()]

    print(parsed)

    for idx, p in enumerate(parsed):
        lbl_A = p[0]
        lbl_B = p[-1]
        pt_A = dict[list(dict.keys())[idx]].PointAt(0)
        pt_B = dict[list(dict.keys())[idx]].PointAt(1)
        dict_pts[lbl_A] = pt_A
        dict_pts[lbl_B] = pt_B

    dict_pts = {k: dict_pts[k] for k in set(dict_pts)}

    return dict_pts


def main(
    i_pt_sabliereA_coordX : float,
    i_pt_sabliereA_coordY : float,
    i_pt_sabliereA_coordZ : float,

    i_pt_sabliereB_coordX : float,
    i_pt_sabliereB_coordY : float,
    i_pt_sabliereB_coordZ : float,

    i_pt_sabliereC_coordX : float,
    i_pt_sabliereC_coordY : float,
    i_pt_sabliereC_coordZ : float,

    i_pt_sabliereD_coordX : float,
    i_pt_sabliereD_coordY : float,
    i_pt_sabliereD_coordZ : float,

    i_pt_pannerefendE_coordX : float,
    i_pt_pannerefendE_coordY : float,
    i_pt_pannerefendE_coordZ : float,

    i_pt_pannerefendF_coordZ : float,

    i_pt_pannerefendG_coordX : float,
    i_pt_pannerefendG_coordY : float,
    i_pt_pannerefendG_coordZ : float,

    i_height_faitiere : float,

    i_panne_rawP_position : float,
    i_panne_rawU_position : float,

    i_coyer_position : float,

    i_jambe_de_force_position : float,
    i_dist_joints_poincon : float
) -> tuple():
    # to the output param component
    o_geos = []
    o_panne_sabliere = []
    o_panne_faitiere = []
    o_entrait_fermes = []
    o_panne = []
    o_poincon = []
    o_jambe_de_force = []
    o_contre_fiche = []
    o_enrayure = []
    o_arbaletrier_demi_croupe = []
    o_arbaletrier = []
    o_arbaletrier_aretier = []
    o_entrait = []
    o_coyer = []
    o_panne_refend = []
    o_chevrons = []

    #TODO: test for export labels
    lbls_lns : dict = {}  # "AB": ln_sabliereAB, ..

    ##########################################################
    # Control points and lines                               #
    ##########################################################
    # the control points present here should be optimized

    # panne sablière
    pt_sabliereA = rg.Point3d(
        i_pt_sabliereA_coordX,
        i_pt_sabliereA_coordY,
        i_pt_sabliereA_coordZ
    )
    pt_sabliereB = rg.Point3d(
        i_pt_sabliereB_coordX,
        i_pt_sabliereB_coordY,
        i_pt_sabliereB_coordZ
    )
    pt_sabliereC = rg.Point3d(
        i_pt_sabliereC_coordX,
        i_pt_sabliereC_coordY,
        i_pt_sabliereC_coordZ
    )
    pt_sabliereD = rg.Point3d(
        i_pt_sabliereD_coordX,
        i_pt_sabliereD_coordY,
        i_pt_sabliereD_coordZ
    )
    ln_sabliereAB = rg.Line(
        pt_sabliereA,
        pt_sabliereB
    )
    ln_sabliereBC = rg.Line(
        pt_sabliereB,
        pt_sabliereC
    )
    ln_sabliereCD = rg.Line(
        pt_sabliereC,
        pt_sabliereD
    )
    ln_sabliereDA = rg.Line(
        pt_sabliereD,
        pt_sabliereA
    )
    o_panne_sabliere.append(ln_sabliereAB)
    o_panne_sabliere.append(ln_sabliereBC)
    o_panne_sabliere.append(ln_sabliereCD)
    o_panne_sabliere.append(ln_sabliereDA)
    lbls_lns["AB"] = ln_sabliereAB
    lbls_lns["BC"] = ln_sabliereBC
    lbls_lns["CD"] = ln_sabliereCD
    lbls_lns["DA"] = ln_sabliereDA

    # panne refend
    pt_E = rg.Point3d(
        i_pt_pannerefendE_coordX,
        i_pt_pannerefendE_coordY,
        i_pt_pannerefendE_coordZ
    )
    pt_G = rg.Point3d(
        i_pt_pannerefendG_coordX,
        i_pt_pannerefendG_coordY,
        i_pt_pannerefendG_coordZ
    )
    ln_EG = rg.Line(pt_E, pt_G)
    pt_F = ln_EG.PointAt(0.5)
    pt_F.Z = i_pt_pannerefendF_coordZ


    ln_pannerefend_EF = rg.Line(pt_E, pt_F)
    ln_pannerefend_FG = rg.Line(pt_F, pt_G)
    o_panne_refend.append(ln_pannerefend_EF)
    o_panne_refend.append(ln_pannerefend_FG)
    lbls_lns["EF"] = ln_pannerefend_EF
    lbls_lns["FG"] = ln_pannerefend_FG

    ##########################################################
    # Generated lines                                        #
    ##########################################################
    # these lines are generated from previous section's elements

    # poincon
    ln_poinconEH, \
    ln_poinconFI, \
    ln_poinconGL = fm.create_poincon(
        ln_pannerefend_EF,
        ln_pannerefend_FG,
        i_height_faitiere
    )
    o_poincon.append(ln_poinconEH)
    o_poincon.append(ln_poinconFI)
    o_poincon.append(ln_poinconGL)
    lbls_lns["EH"] = ln_poinconEH
    lbls_lns["FI"] = ln_poinconFI
    lbls_lns["GL"] = ln_poinconGL

    # coyer
    ln_coyerAE, \
    ln_coyerBG, \
    ln_coyerCG, \
    ln_coyerDE = fm.create_coyer(
        ln_poinconEH,
        ln_poinconGL,
        ln_sabliereAB,
        ln_sabliereCD,
    )

    # arbaletriers
    ln_arbaletrierHO, ln_arbaletrierIP, ln_arbaletrierLQ, \
    ln_arbaletrierHT, ln_arbaletrierIS, ln_arbaletrierLR = fm.create_arbaletrier(
        ln_poinconEH,
        ln_poinconFI,
        ln_poinconGL,
        ln_sabliereAB,
        ln_sabliereCD,
    )
    o_arbaletrier.append(ln_arbaletrierHO)
    o_arbaletrier.append(ln_arbaletrierIP)
    o_arbaletrier.append(ln_arbaletrierLQ)
    o_arbaletrier.append(ln_arbaletrierHT)
    o_arbaletrier.append(ln_arbaletrierIS)
    o_arbaletrier.append(ln_arbaletrierLR)
    lbls_lns["HO"] = ln_arbaletrierHO
    lbls_lns["IP"] = ln_arbaletrierIP
    lbls_lns["LQ"] = ln_arbaletrierLQ
    lbls_lns["HT"] = ln_arbaletrierHT
    lbls_lns["IS"] = ln_arbaletrierIS
    lbls_lns["LR"] = ln_arbaletrierLR

    # arbaletrier aretier
    ln_arbaletrier_aretierHA, \
    ln_arbaletrier_aretierLB, \
    ln_arbaletrier_aretierLC, \
    ln_arbaletrier_aretierHD = fm.create_arbaletrier_aretier(
        ln_poinconEH,
        ln_poinconGL,
        ln_sabliereAB,
        ln_sabliereCD
    )
    o_arbaletrier_aretier.append(ln_arbaletrier_aretierHA)
    o_arbaletrier_aretier.append(ln_arbaletrier_aretierLB)
    o_arbaletrier_aretier.append(ln_arbaletrier_aretierLC)
    o_arbaletrier_aretier.append(ln_arbaletrier_aretierHD)
    lbls_lns["HA"] = ln_arbaletrier_aretierHA
    lbls_lns["LB"] = ln_arbaletrier_aretierLB
    lbls_lns["LC"] = ln_arbaletrier_aretierLC
    lbls_lns["HD"] = ln_arbaletrier_aretierHD

    # entrait
    ln_entraitEO, ln_entraitFP, ln_entraitGQ, \
    ln_entraitET, ln_entraitFS, ln_entraitGR = fm.create_entrait(
        ln_poinconEH,
        ln_poinconFI,
        ln_poinconGL,

        ln_arbaletrierHO,
        ln_arbaletrierIP,
        ln_arbaletrierLQ,
        ln_arbaletrierHT,
        ln_arbaletrierIS,
        ln_arbaletrierLR,

        ln_sabliereAB,
        ln_sabliereCD
    )
    o_entrait.append(ln_entraitEO)
    o_entrait.append(ln_entraitFP)
    o_entrait.append(ln_entraitGQ)
    o_entrait.append(ln_entraitET)
    o_entrait.append(ln_entraitFS)
    o_entrait.append(ln_entraitGR)
    lbls_lns["EO"] = ln_entraitEO
    lbls_lns["FP"] = ln_entraitFP
    lbls_lns["GQ"] = ln_entraitGQ
    lbls_lns["ET"] = ln_entraitET
    lbls_lns["FS"] = ln_entraitFS
    lbls_lns["GR"] = ln_entraitGR

    # arbaletrier demi croupe
    ln_arbaletrier_demi_croupeLN, ln_arbaletrier_demi_croupeHM = fm.create_arbaletrier_demi_croupe(
        ln_poinconEH,
        ln_poinconGL,
        ln_sabliereBC,
        ln_sabliereDA
    )
    o_arbaletrier_demi_croupe.append(ln_arbaletrier_demi_croupeHM)
    o_arbaletrier_demi_croupe.append(ln_arbaletrier_demi_croupeLN)
    lbls_lns["HM"] = ln_arbaletrier_demi_croupeHM
    lbls_lns["LN"] = ln_arbaletrier_demi_croupeLN

    # entrait fermes
    ln_entrait_fermeEM, ln_entrait_fermeGN = fm.create_entrait_fermes(
        ln_poinconEH,
        ln_poinconGL,

        ln_arbaletrier_demi_croupeHM,
        ln_arbaletrier_demi_croupeLN,
    )
    o_entrait_fermes.append(ln_entrait_fermeEM)
    o_entrait_fermes.append(ln_entrait_fermeGN)
    lbls_lns["EM"] = ln_entrait_fermeEM
    lbls_lns["GN"] = ln_entrait_fermeGN

    # panne
    ln_panneP1P2, ln_panneP2P3, ln_panneP3P4, ln_panneP4P5, \
    ln_panneP5P6, ln_panneP6P7, ln_panneP7P8, ln_panneP8P9, \
    ln_panneP9P10, ln_panneP10P11, ln_panneP11P12, ln_panneP12P1, \
    ln_panneU1U2, ln_panneU2U3, ln_panneU3U4, ln_panneU4U5, \
    ln_panneU5U6, ln_panneU6U7, ln_panneU7U8, ln_panneU8U9, \
    ln_panneU9U10, ln_panneU10U11, ln_panneU11U12, ln_panneU12U1 = fm.create_panne(
        ln_arbaletrierHO,
        ln_arbaletrierIP,
        ln_arbaletrierLQ,
        ln_arbaletrierHT,
        ln_arbaletrierIS,
        ln_arbaletrierLR,

        ln_arbaletrier_aretierHA,
        ln_arbaletrier_aretierLB,
        ln_arbaletrier_aretierLC,
        ln_arbaletrier_aretierHD,

        ln_arbaletrier_demi_croupeHM,
        ln_arbaletrier_demi_croupeLN,

        i_panne_rawP_position,
        i_panne_rawU_position
    )
    o_panne.append(ln_panneP1P2)
    o_panne.append(ln_panneP2P3)
    o_panne.append(ln_panneP3P4)
    o_panne.append(ln_panneP4P5)
    o_panne.append(ln_panneP5P6)
    o_panne.append(ln_panneP6P7)
    o_panne.append(ln_panneP7P8)
    o_panne.append(ln_panneP8P9)
    o_panne.append(ln_panneP9P10)
    o_panne.append(ln_panneP10P11)
    o_panne.append(ln_panneP11P12)
    o_panne.append(ln_panneP12P1)
    o_panne.append(ln_panneU1U2)
    o_panne.append(ln_panneU2U3)
    o_panne.append(ln_panneU3U4)
    o_panne.append(ln_panneU4U5)
    o_panne.append(ln_panneU5U6)
    o_panne.append(ln_panneU6U7)
    o_panne.append(ln_panneU7U8)
    o_panne.append(ln_panneU8U9)
    o_panne.append(ln_panneU9U10)
    o_panne.append(ln_panneU10U11)
    o_panne.append(ln_panneU11U12)
    o_panne.append(ln_panneU12U1)
    lbls_lns["P1P2"] = ln_panneP1P2
    lbls_lns["P2P3"] = ln_panneP2P3
    lbls_lns["P3P4"] = ln_panneP3P4
    lbls_lns["P4P5"] = ln_panneP4P5
    lbls_lns["P5P6"] = ln_panneP5P6
    lbls_lns["P6P7"] = ln_panneP6P7
    lbls_lns["P7P8"] = ln_panneP7P8
    lbls_lns["P8P9"] = ln_panneP8P9
    lbls_lns["P9P10"] = ln_panneP9P10
    lbls_lns["P10P11"] = ln_panneP10P11
    lbls_lns["P11P12"] = ln_panneP11P12
    lbls_lns["P12P1"] = ln_panneP12P1
    lbls_lns["U1U2"] = ln_panneU1U2
    lbls_lns["U2U3"] = ln_panneU2U3
    lbls_lns["U3U4"] = ln_panneU3U4
    lbls_lns["U4U5"] = ln_panneU4U5
    lbls_lns["U5U6"] = ln_panneU5U6
    lbls_lns["U6U7"] = ln_panneU6U7
    lbls_lns["U7U8"] = ln_panneU7U8
    lbls_lns["U8U9"] = ln_panneU8U9
    lbls_lns["U9U10"] = ln_panneU9U10
    lbls_lns["U10U11"] = ln_panneU10U11
    lbls_lns["U11U12"] = ln_panneU11U12
    lbls_lns["U12U1"] = ln_panneU12U1

    # enrayure
    ln_coyerAC2, ln_coyerBF4, ln_coyerCF2, ln_coyerDC4, \
    ln_enrayureE1E3, ln_enrayureF1F3, ln_enrayureF3F5, ln_enrayureG1G3, \
    ln_enrayureC3C1, ln_enrayureB3B1, ln_enrayureD1D3, ln_enrayureC1C5 = fm.create_enrayure(
        ln_coyerAE,
        ln_coyerBG,
        ln_coyerCG,
        ln_coyerDE,

        ln_entraitGR,
        ln_entraitGQ,
        ln_entraitEO,
        ln_entraitET,
        ln_entrait_fermeGN,
        ln_entrait_fermeEM,

        ln_sabliereAB,
        ln_sabliereBC,
        ln_sabliereCD,
        ln_sabliereDA,

        i_coyer_position
    )
    o_enrayure.append(ln_enrayureE1E3)
    o_enrayure.append(ln_enrayureF1F3)
    o_enrayure.append(ln_enrayureF3F5)
    o_enrayure.append(ln_enrayureG1G3)
    o_enrayure.append(ln_enrayureC3C1)
    o_enrayure.append(ln_enrayureB3B1)
    o_enrayure.append(ln_enrayureD1D3)
    o_enrayure.append(ln_enrayureC1C5)
    lbls_lns["E1E3"] = ln_enrayureE1E3
    lbls_lns["F1F3"] = ln_enrayureF1F3
    lbls_lns["F3F5"] = ln_enrayureF3F5
    lbls_lns["G1G3"] = ln_enrayureG1G3
    lbls_lns["C3C1"] = ln_enrayureC3C1
    lbls_lns["B3B1"] = ln_enrayureB3B1
    lbls_lns["D1D3"] = ln_enrayureD1D3
    lbls_lns["C1C5"] = ln_enrayureC1C5

    o_coyer.append(ln_coyerAC2)
    o_coyer.append(ln_coyerBF4)
    o_coyer.append(ln_coyerCF2)
    o_coyer.append(ln_coyerDC4)
    lbls_lns["AC2"] = ln_coyerAC2
    lbls_lns["BF4"] = ln_coyerBF4
    lbls_lns["CF2"] = ln_coyerCF2
    lbls_lns["DC4"] = ln_coyerDC4

    # panne faitiere
    ln_faitiereLH = fm.create_panne_faitiere(
        ln_poinconEH,
        ln_poinconFI,
        ln_poinconGL
    )
    o_panne_faitiere.append(ln_faitiereLH)
    lbls_lns["LH"] = ln_faitiereLH

    # jambe de force
    ln_jdfP1Y1, ln_jdfP2Y2, ln_jdfP3Y3, ln_jdfP4Y4, \
    ln_jdfP5Y5, ln_jdfP6Y6, ln_jdfP7Y7, ln_jdfP8Y8, \
    ln_jdfP9Y9, ln_jdfP10Y10, ln_jdfP11Y11, ln_jdfP12Y12 = fm.create_jambe_de_force(
        ln_panneP1P2,
        ln_panneP2P3,
        ln_panneP3P4,
        ln_panneP4P5,
        ln_panneP5P6,
        ln_panneP6P7,
        ln_panneP7P8,
        ln_panneP8P9,
        ln_panneP9P10,
        ln_panneP10P11,
        ln_panneP11P12,
        ln_panneP12P1,
        ln_panneU1U2,
        ln_panneU2U3,
        ln_panneU3U4,
        ln_panneU4U5,
        ln_panneU5U6,
        ln_panneU6U7,
        ln_panneU7U8,
        ln_panneU8U9,
        ln_panneU9U10,
        ln_panneU10U11,
        ln_panneU11U12,
        ln_panneU12U1,

        ln_coyerAE,
        ln_coyerBG,
        ln_coyerCG,
        ln_coyerDE,

        ln_entraitEO,
        ln_entraitFP,
        ln_entraitGQ,
        ln_entraitET,
        ln_entraitFS,
        ln_entraitGR,

        ln_entrait_fermeEM,
        ln_entrait_fermeGN,

        i_jambe_de_force_position
    )
    o_jambe_de_force.append(ln_jdfP1Y1)
    o_jambe_de_force.append(ln_jdfP2Y2)
    o_jambe_de_force.append(ln_jdfP3Y3)
    o_jambe_de_force.append(ln_jdfP4Y4)
    o_jambe_de_force.append(ln_jdfP5Y5)
    o_jambe_de_force.append(ln_jdfP6Y6)
    o_jambe_de_force.append(ln_jdfP7Y7)
    o_jambe_de_force.append(ln_jdfP8Y8)
    o_jambe_de_force.append(ln_jdfP9Y9)
    o_jambe_de_force.append(ln_jdfP10Y10)
    o_jambe_de_force.append(ln_jdfP11Y11)
    o_jambe_de_force.append(ln_jdfP12Y12)
    lbls_lns["P1Y1"] = ln_jdfP1Y1
    lbls_lns["P2Y2"] = ln_jdfP2Y2
    lbls_lns["P3Y3"] = ln_jdfP3Y3
    lbls_lns["P4Y4"] = ln_jdfP4Y4
    lbls_lns["P5Y5"] = ln_jdfP5Y5
    lbls_lns["P6Y6"] = ln_jdfP6Y6
    lbls_lns["P7Y7"] = ln_jdfP7Y7
    lbls_lns["P8Y8"] = ln_jdfP8Y8
    lbls_lns["P9Y9"] = ln_jdfP9Y9
    lbls_lns["P10Y10"] = ln_jdfP10Y10
    lbls_lns["P11Y11"] = ln_jdfP11Y11
    lbls_lns["P12Y12"] = ln_jdfP12Y12

    # contre fiche
    ln_ctrficheK4K5, ln_ctrficheK4K3, \
    ln_ctrficheK9K2, ln_ctrficheK9K6, \
    ln_ctrficheK7K1, ln_ctrficheK7K8, \
    ln_ctrficheZ4Z2, ln_ctrficheZ4Z3, \
    ln_ctrficheZ6Z1, ln_ctrficheZ6Z5, \
    ln_ctrficheX4X5, ln_ctrficheX4X3, \
    ln_ctrficheX6X1, ln_ctrficheX6X7, \
    ln_ctrficheX8X2, ln_ctrficheX8X9 = fm.create_contre_fiche(
        ln_poinconEH,
        ln_poinconFI,
        ln_poinconGL,

        ln_arbaletrierHO,
        ln_arbaletrierIP,
        ln_arbaletrierLQ,
        ln_arbaletrierHT,
        ln_arbaletrierIS,
        ln_arbaletrierLR,

        ln_arbaletrier_aretierHA,
        ln_arbaletrier_aretierLB,
        ln_arbaletrier_aretierLC,
        ln_arbaletrier_aretierHD,

        ln_arbaletrier_demi_croupeHM,
        ln_arbaletrier_demi_croupeLN,

        ln_faitiereLH,

        i_dist_joints_poincon
    )
    o_contre_fiche.append(ln_ctrficheK4K5)
    o_contre_fiche.append(ln_ctrficheK4K3)
    o_contre_fiche.append(ln_ctrficheK9K2)
    o_contre_fiche.append(ln_ctrficheK9K6)
    o_contre_fiche.append(ln_ctrficheK7K1)
    o_contre_fiche.append(ln_ctrficheK7K8)
    o_contre_fiche.append(ln_ctrficheZ4Z2)
    o_contre_fiche.append(ln_ctrficheZ4Z3)
    o_contre_fiche.append(ln_ctrficheZ6Z1)
    o_contre_fiche.append(ln_ctrficheZ6Z5)
    o_contre_fiche.append(ln_ctrficheX4X5)
    o_contre_fiche.append(ln_ctrficheX4X3)
    o_contre_fiche.append(ln_ctrficheX6X1)
    o_contre_fiche.append(ln_ctrficheX6X7)
    o_contre_fiche.append(ln_ctrficheX8X2)
    o_contre_fiche.append(ln_ctrficheX8X9)
    lbls_lns["K4K5"] = ln_ctrficheK4K5
    lbls_lns["K4K3"] = ln_ctrficheK4K3
    lbls_lns["K9K2"] = ln_ctrficheK9K2
    lbls_lns["K9K6"] = ln_ctrficheK9K6
    lbls_lns["K7K1"] = ln_ctrficheK7K1
    lbls_lns["K7K8"] = ln_ctrficheK7K8
    lbls_lns["Z4Z2"] = ln_ctrficheZ4Z2
    lbls_lns["Z4Z3"] = ln_ctrficheZ4Z3
    lbls_lns["Z6Z1"] = ln_ctrficheZ6Z1
    lbls_lns["Z6Z5"] = ln_ctrficheZ6Z5
    lbls_lns["X4X5"] = ln_ctrficheX4X5
    lbls_lns["X4X3"] = ln_ctrficheX4X3
    lbls_lns["X6X1"] = ln_ctrficheX6X1
    lbls_lns["X6X7"] = ln_ctrficheX6X7
    lbls_lns["X8X2"] = ln_ctrficheX8X2
    lbls_lns["X8X9"] = ln_ctrficheX8X9

    ##########################################################
    # Labels                                                 #
    ##########################################################
    # list of text labels for control points and lines labels
    o_pts = []
    o_lns = []
    o_pts_labels : list(str) = []
    o_lns_ptmids_labels : list(str) = []

    o_lns_ptmids = [ln.PointAt(0.5) for ln in list(lbls_lns.values())]
    o_lns_ptmids_labels = list(lbls_lns.keys())

    temp_dict = extract_lbl(lbls_lns)
    for k, v in temp_dict.items():
        o_pts.append(v)
        o_pts_labels.append(k)

    return \
    o_panne_sabliere, \
    o_panne_faitiere, \
    o_entrait_fermes, \
    o_panne, \
    o_poincon, \
    o_jambe_de_force, \
    o_contre_fiche, \
    o_enrayure, \
    o_arbaletrier_demi_croupe, \
    o_arbaletrier, \
    o_arbaletrier_aretier, \
    o_entrait, \
    o_coyer, \
    o_panne_refend, \
    o_chevrons, \
    o_pts, \
    o_lns_ptmids, \
    o_pts_labels, \
    o_lns_ptmids_labels


if __name__ == "__main__":
    print(f"Running ctr_pts.py")
    o_panne_sabliere, \
    o_panne_faitiere, \
    o_entrait_fermes, \
    o_panne, \
    o_poincon, \
    o_jambe_de_force, \
    o_contre_fiche, \
    o_enrayure, \
    o_arbaletrier_demi_croupe, \
    o_arbaletrier, \
    o_arbaletrier_aretier, \
    o_entrait, \
    o_coyer, \
    o_panne_refend, \
    o_chevrons, \
    o_pts, \
    o_lns_ptmids, \
    o_pts_labels, \
    o_lns_ptmids_labels = main(
        i_pt_sabliereA_coordX,
        i_pt_sabliereA_coordY,
        i_pt_sabliereA_coordZ,

        i_pt_sabliereB_coordX,
        i_pt_sabliereB_coordY,
        i_pt_sabliereB_coordZ,

        i_pt_sabliereC_coordX,
        i_pt_sabliereC_coordY,
        i_pt_sabliereC_coordZ,

        i_pt_sabliereD_coordX,
        i_pt_sabliereD_coordY,
        i_pt_sabliereD_coordZ,

        i_pt_pannerefendE_coordX,
        i_pt_pannerefendE_coordY,
        i_pt_pannerefendE_coordZ,

        i_pt_pannerefendF_coordZ,

        i_pt_pannerefendG_coordX,
        i_pt_pannerefendG_coordY,
        i_pt_pannerefendG_coordZ,

        i_height_faitiere,

        i_panne_rawP_position,
        i_panne_rawU_position,

        i_coyer_position,

        i_jambe_de_force_position,
        i_dist_joints_poincon
    )
    print(f"End file for {__name__}.py")



