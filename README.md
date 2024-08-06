# hgr
HGR is a open source, non optimized and basic graphic programming helper for Windows users.
<br>
HGR (Hasan Graphics)
<br>
<br>
<h3>Usage:</h3>
<br>
Download as zip or use <pre>https://github.com/HasanEfeAksoy/hgr.git</pre> command.
<br>
<br>
Include: <pre>#include "hgr.h"</pre>
<br>
<br>
Example: 
<pre>
    #include <iostream>
    #include "hgr.h"
    <br>
    <br>
    void update();
    <br>
    int main() {
      <br>
      &ensp&ensp&ensp&ensp hgr::drawWindow(400, 400, "HGR (Hasan Graphics) Window", 0, 0, 0, update);
      <br>
      &ensp&ensp&ensp&enspreturn 0;
      <br>
    }
      <br>
      <br>
    
    void update() {
      <br>
      &ensp&ensp&ensp&ensphgr::drawPixel(100, 100, 255, 255, 255);
      <br>
    }
</pre>
<br>
