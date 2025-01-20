
        //解密
        function xorCrypto(data, key) {
    var decrypted = '';
    for (var i = 0; i < data.length; i++) {
        // 将字符转换为其ASCII码，进行XOR操作，然后再转换回字符
        var keyChar = key.charCodeAt(0); // 获取密钥字符的ASCII码
        var dataChar = data.charCodeAt(i); // 获取数据字符的ASCII码
        var xorChar = String.fromCharCode(dataChar ^ keyChar); // XOR操作后转换回字符
        decrypted += xorChar;
    }
        return decrypted;
    }

    var JS = 1;
        // 创建XMLHttpRequest对象
        var xhr = new XMLHttpRequest();
        // 配置请求的类型（GET），URL，以及是否异步
        xhr.open('GET', 'http://127.0.0.1:9912?IDio=KE1&', true);
        // 发送请求
        xhr.send();
        xhr.onreadystatechange = function(){if (xhr.readyState === XMLHttpRequest.DONE){
            if (xhr.status === 200) {
                JS = xhr.responseText;
                JS= xorCrypto(JS,'A');
                //document.write(JS);
                document.getElementById('Imme').innerHTML +=JS;
                } else {
                    alert(xhr.status);
                    document.getElementById('Imme').innerHTML += '<h1>EREER</h1>'
                }
            }
        }
