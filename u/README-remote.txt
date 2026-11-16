all-routes inert remote staging (upload these files to the u/ directory verbatim).
  marker.txt  plain-text marker used by A13/A14/A16 download primitives
  probe.cmd   batch writing %PUBLIC%\A12-ok.txt (A12 second stage)
  ftp.cmd     batch writing %PUBLIC%\A17-ok.txt (A17 second stage)
  probe.sct   scriptlet writing %PUBLIC%\A11-ok.txt (A11 regsvr32 /i:)
  probe.svg   mshta-loadable SVG writing %PUBLIC%\A10-ok.txt (A10 control)
  probe.chm   compiled HTML help writing %PUBLIC%\A05-ok.txt on capable builds (A05)
  a19.chm     compiled HTML help whose stage2.cmd writes %PUBLIC%\A19-ok.txt when extracted via hh -decompile (A19)
  direct.msi  per-user MSI whose Type-37 CustomAction writes %PUBLIC%\A03-ok.txt (A03)
  base.msi    same skeleton without the CustomAction (A04 base)
  marker.mst  transform adding the A04 CustomAction to base.msi
  catalog.pdf benign fixture PDF (lure content; byte-generated, no secrets)
All content is inert marker material. No payload, no C2, no x2.dat linkage.
