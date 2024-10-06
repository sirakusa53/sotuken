/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package vmdlc;

import java.io.FileOutputStream;
import java.io.IOException;

import specfile.BitWidthDef;
import specfile.InsnRepresentationDef;
import specfile.DatatypeDef;
import specfile.InstructionDef;
import specfile.SpecFile;
import specfile.SuperinstructionSpec;

import type.TypeDefinition;
import type.VMDataType;

public class SpecFileGen {
    public static void main(String args[]) throws IOException {
        SpecFile spec = new SpecFile();

        String outFileName = null;
        String fingerprintFileName = null;

        int optInsnWidth = 0;
        int optJSVWidth = 0;
        int optAlignWidth = 0;

        InsnRepresentationDef insnRepresentationDef = new InsnRepresentationDef();

        int i = 0;
        while (i < args.length) {
            if (args[i].equals("--bitwidth-insn"))
                optInsnWidth = Integer.parseInt(args[++i]);
            else if (args[i].equals("--bitwidth-jsv"))
                optJSVWidth = Integer.parseInt(args[++i]);
            else if (args[i].equals("--bitwidth-align"))
                optAlignWidth = Integer.parseInt(args[++i]);
            else if (args[i].equals("--accept-sbc"))
                insnRepresentationDef.addInsnType("sbc");
            else if (args[i].equals("--accept-obc"))
                insnRepresentationDef.addInsnType("obc");
            else if (args[i].equals("--accept-ei"))
                insnRepresentationDef.addInsnType("ei");
            else if (args[i].equals("--datatype")) {
                String fileName = args[++i];
                TypeDefinition.load(fileName);
                spec.setDatatypeDef(DatatypeDef.generateFromVMDataType(VMDataType.all()));
            } else if (args[i].equals("--insndef")) {
                String fileName = args[++i];
                spec.setInstructionDef(InstructionDef.loadFromFile(fileName));
            } else if (args[i].equals("--sispec")) {
                String fileName = args[++i];
                spec.setSuperinstructionSpec(SuperinstructionSpec.loadFromFile(fileName));
            } else if (args[i].equals("-o"))
                outFileName = args[++i];
            else if (args[i].equals("--fingerprint"))
                fingerprintFileName = args[++i];
            else
                throw new Error("Unknown option: "+args[i]);
            i++;
        }
        spec.setBitWidthDef(BitWidthDef.generateFromValue(optInsnWidth, optJSVWidth, optAlignWidth));
        spec.setInsnRepresentationDef(insnRepresentationDef);
        if (outFileName == null)
            System.out.print(spec.unparse());
        else {
            try (FileOutputStream out = new FileOutputStream(outFileName)) {
                out.write(spec.unparse().getBytes());
                out.flush();
            }
        }
        if (fingerprintFileName != null) {
            try (FileOutputStream out = new FileOutputStream(fingerprintFileName)) {
                String f = String.format("0x%02x\n", spec.getFingerprint());
                out.write(f.getBytes());
                out.flush();
            }
        }
    }
}
