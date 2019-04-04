Thư viện xử lý frame truyền nhận:

- Trong file driver.c
  + Implement hàm truyền low-level vào hàm FDRV_UartSend_LL. Ví dụ truyền UART, BLE...
  + Implement hàm get tick mili giây vào hàm FDRV_GetTick_LL.

- Trong file frame_app.c
  + Modify bảng cmd_table theo ý muốn.
  + Implement các hàm callback CallbackFcn1, CallbackFcn2.

- Tạo một ring mới cho app và gọi Frame_Init.
- Khi nhận được data, gọi hàm Ring_WriteByte để write data mới vào ring.
- Khi muốn đóng gói và gửi frame, gọi hàm Frame_Send.
- Gọi liên tục hàm Frame_Receive(). Nó sẽ tự xử lý và đối chiếu cmd, gọi các hàm callback tương ứng
đã khai báo ở trên.
