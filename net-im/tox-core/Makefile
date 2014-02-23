# Created by: Derek Musselmann aka phrac <derek@disflux.com>
# $FreeBSD$

PORTNAME=	tox-core
PORTVERSION=	20140223
CATEGORIES=	net-im
MASTER_SITES=	GH

MAINTAINER=	derek@disflux.com
COMMENT=	A free as in freedom Skype replacement.

LICENSE=	GPLv3

LIB_DEPENDS=	libsodium.so:${PORTSDIR}/security/libsodium

USE_GITHUB=	yes
GH_ACCOUNT=	irungentoo
GH_PROJECT=	ProjectTox-Core
GH_COMMIT=	f219fb4
GH_TAGNAME=	${GH_COMMIT}

DIST_SUBDIR=	${PORTNAME}

USE_AUTOTOOLS=	autoconf

USES=		pathfix

CONFIGURE_ARGS+=--with-pkgconfigdir=${LOCALDIR}/libdata/pkgconfig

pre-configure:
	@cd ${WRKSRC} && ${SH} autogen.sh

post-patch:
	@${REINPLACE_CMD} -e 's|(libdir)|{LOCALDIR}/libdata|g' ${WRKSRC}/Makefile.am

.include <bsd.port.mk>
