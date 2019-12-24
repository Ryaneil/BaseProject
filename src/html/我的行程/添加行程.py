import wx
app=wx.App(False)

win=wx.Frame(None,title='今日行程',size=(410,335))
bg=wx.Panel(win)
def load(event):
    a=open(fileload.GetValue())
    contents.SetValue(a.read())
    a.close()
def save(event):
    c=open(fileload.GetValue(),'w')
    c.write(contents.GetValue())
    c.close()
fileload=wx.TextCtrl(bg)
contents=wx.TextCtrl(bg,style=wx.TE_MULTILINE|wx.HSCROLL)
savebutton=wx.Button(bg,label='儲存')
savebutton.Bind(wx.EVT_BUTTON,save)
level=wx.BoxSizer()
level.Add(fileload,proportion=1,flag=wx.EXPAND)
level.Add(savebutton,proportion=0,flag=wx.LEFT,border=5)
down=wx.BoxSizer(wx.VERTICAL)
down.Add(level,proportion=0,flag=wx.EXPAND|wx.ALL,border=5)
down.Add(contents,proportion=1,flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.BOTTOM,border=5)
bg.SetSizer(down)
win.Show()
app.MainLoop()
