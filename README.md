# hgr
HGR is a open source, unoptimized and basic graphic programming helper for Windows users.
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
    #include &lt iostream &gt
    #include "hgr.h"
    <br>
    <br>
    void update();
    <br>
    int main() {
      <br>
      &nbsp &nbsp &nbsp &nbsp hgr::drawWindow(400, 400, "HGR (Hasan Graphics) Window", 0, 0, 0, update);
      <br>
      &nbsp &nbsp &nbsp &nbsp return 0;
      <br>
    }
    <br>
    <br>
    void update() {
      <br>
      &nbsp &nbsp &nbsp &nbsp hgr::drawPixel(100, 100, 255, 255, 255);
      <br>
    }
</pre>
<br>
