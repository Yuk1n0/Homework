package listener;

import javax.servlet.ServletRequestEvent;
import javax.servlet.ServletRequestListener;
import javax.servlet.http.HttpServletRequest;

public class ListenerTest implements ServletRequestListener {
    @Override
    public void requestInitialized(ServletRequestEvent arg0) {
        HttpServletRequest request = (HttpServletRequest) arg0.getServletRequest();
        String uri = request.getRequestURI();
        uri = request.getQueryString() == null ? uri : (uri + "?" + request.getQueryString());
        request.setAttribute("dateCreated", System.currentTimeMillis());
        System.out.println("IP Address: " + request.getRemoteAddr() + " 请求 " + uri);
    }

    @Override
    public void requestDestroyed(ServletRequestEvent arg0) {
        HttpServletRequest request = (HttpServletRequest) arg0.getServletRequest();
        long time = System.currentTimeMillis() - (long) request.getAttribute("dateCreated");
        System.out.println(request.getRemoteAddr() + "请求处理结束，用时" + time + "ms");
    }
}