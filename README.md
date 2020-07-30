# DoHoaCK
<p>B1. Download Project từ Github và giải nén. Chạy file DoAnDHMT.sln</p>
<p>B2. Chuột phải vào Project chọn mục Properties</p>
<p>B3. Trong mục C/C++, chọn mục General và thêm đường dẫn đến file include ( file include đã có sẵn trong project ) trong phần Additional Include Directories từ máy bạn</p>
<p>B4. Trong mục Linker, chọn mục General và thêm đường dẫn đến file lib ( file lib đã có sẵn trong project ) trong phần Additional Library Directories từ máy bạn</p>
<p>B5. Kiểm tra trong phần Linker mục Input, mục Additional Dependencies đã add các tên file:</p>
<p>Glaux.lib</p>
<p>GLU32.LIB</p>
<p>glut32.lib</p>
<p>OPENGL32.LIB</p>
<p>glui32.lib</p>
<p>Nếu chưa có thì ta add các tên file này vào sau đó nhấn 'OK' để lưu.</p>
<p>B6. Sau đó click 'OK' để lưu và Build Project.</p>
