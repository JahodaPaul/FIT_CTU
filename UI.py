from tkinter import *

class UI:

    def __init__(self, master):

        self.frame = Frame(master)
        self.frame.pack()
        self.buttonList = []
        self.y = 2
        # self.button2 = Button(self.frame,text="test",command=self.button2.destroy(self.button2))

        self.button = Button(self.frame, text="KONEC", fg="red", command=master.destroy)
        # self.button.pack(side=LEFT)
        self.button.grid(row=0,column=1)

        self.hi_there = Button(self.frame, text="Pozdrav!", command=self.rekni_ahoj)
        # self.hi_there.pack(side=LEFT)
        self.hi_there.grid(row=1,column=1)

    def rekni_ahoj(self):
        self.buttonList.append(Button(self.frame,text="test"))
        # self.button2.pack(side=LEFT)
        self.buttonList[-1]['command'] = lambda specificButton=self.buttonList[-1]: self.destroyButton(specificButton)
        if self.y%2==0:
            self.buttonList[-1].grid(row=self.y,column = 1)
        else:
            self.buttonList[-1].grid(row=self.y, column=0)
        self.y += 1
        print(self.y)
        # self.button2.grid(row=5,column=5)

    def destroyButton(self,specificButton):
        specificButton.destroy()
        self.y -= 1
        print(self.y)

    # def destroy(self,button):
    #     button.unbind()
